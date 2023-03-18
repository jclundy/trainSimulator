#include "junctiontrack.h"
#include "track_system/collisionchecker.h"

#include <math.h>

JunctionTrack::JunctionTrack(unsigned int id, float length, const QPointF &position, unsigned int maxBranches):
    m_forwardJunction(this, maxBranches),
    m_rearJunction(this, maxBranches)
{
    m_id = id;
    m_rearSignal = NULL;
    m_frontSignal = NULL;
    m_trackGeometry = new TrackGeometry(length, position);
    m_frontSensor = new TrackSensor(0);
    m_rearSensor = new TrackSensor(length);
}

JunctionTrack::~JunctionTrack() {
    disconnectFromNeighbours();
    delete m_trackGeometry;
    delete m_frontSensor;
    delete m_rearSensor;
}

// ITrackSegment Interface
track_segment_type JunctionTrack::getType() {
    return JUNCTION_TRACK;
}

bool JunctionTrack::isJunction() {
    return true;
}
bool JunctionTrack::isLinear() {
    return false;
}

bool JunctionTrack::isFrontTerminal()  {
    return m_forwardJunction.getNumBranches() == 0;
}

bool JunctionTrack::isRearTerminal() {
    return m_rearJunction.getNumBranches() == 0;
}

ITrackSegment* JunctionTrack::getSelectedForwardEnd() {
    return m_forwardJunction.getSelectedBranch();
}
ITrackSegment* JunctionTrack::getSelectedRearEnd() {
    return m_rearJunction.getSelectedBranch();
}
QList<ITrackSegment*> JunctionTrack::getForwardNeighbours() {
    return m_forwardJunction.getBranches();
}
QList<ITrackSegment*> JunctionTrack::getRearNeighbours() {
   return m_rearJunction.getBranches();
}

bool JunctionTrack::isConnectedForward() {
    if(isFrontTerminal()) {
        return false;
    }

    return getSelectedForwardEnd()->getSelectedRearEnd() == this;
}

bool JunctionTrack::isConnectedReverse() {
    if(isRearTerminal()) {
        return false;
    }
    return getSelectedRearEnd()->getSelectedForwardEnd() == this;
}

bool JunctionTrack::connectRearToTrack(ITrackSegment *track) {
    // do not allow a junction to be connected to a junction
    if(track->isJunction()) {
        return false;
    }
    // also ensure track front is a terminal
    if(track->isFrontTerminal() == false) {
        return false;
    }

    bool success = m_rearJunction.addBranch(track);
    if(success) {
        track->addFrontConnection(this);
        updateRearPosition(track);
    }
    return success;
}

bool JunctionTrack::connectFrontToTrack(ITrackSegment *track) {
    // do not allow a junction to be connected to a junction
    if(track->isJunction()) {
        return false;
    }
    // also ensure track rear is a terminal
    if(track->isRearTerminal() == false) {
        return false;
    }

    bool success = m_forwardJunction.addBranch(track);
    if(success) {
        track->addRearConnection(this);
        updateFrontPosition(track);
    }
    return success;
}

void JunctionTrack::disconnectFromTrackSegment(ITrackSegment *track) {
    m_forwardJunction.removeBranch(track);
    m_rearJunction.removeBranch(track);
}

void JunctionTrack::updateRearPosition(ITrackSegment* track) {
    bool rearWasInitiallyTerminal = m_rearJunction.getNumBranches() == 1;
    if(rearWasInitiallyTerminal && isFrontTerminal()) {
        // if both junctions were terminals, move both junctions
        QPointF delta = track->getTrackGeometry()->getFrontEndPosition() - m_trackGeometry->getRearEndPosition();
        m_trackGeometry->translate(delta);

    } else if (track->isLinear()){
        // this check is required to avoid infinite recursion if track is a junction

        // if our junction already has a connection,
        // update the track's front end position
        track->updateFrontPosition(this);
    } else {
        m_trackGeometry->setRearPosition(track->getTrackGeometry()->getFrontEndPosition());
    }
}

void JunctionTrack::updateFrontPosition(ITrackSegment* track) {
    bool frontWasInitiallyTerminal = m_forwardJunction.getNumBranches() == 1;

    if(frontWasInitiallyTerminal && isRearTerminal()) {
        QPointF delta = track->getTrackGeometry()->getRearEndPosition() - m_trackGeometry->getFrontEndPosition();
        m_trackGeometry->translate(delta);
    } else if (track->isLinear()){
        // this check is required to avoid infinite recursion if track is a junction

        // if our junction already has a connection,
        // update the track's rear end position
        track->updateRearPosition(this);
    } else {
        m_trackGeometry->setForwardPosition(track->getTrackGeometry()->getRearEndPosition());
    }
}

void JunctionTrack::addFrontConnection(ITrackSegment* track) {
    Q_UNUSED(track);
}

void JunctionTrack::addRearConnection(ITrackSegment* track) {
    Q_UNUSED(track);
}

// connectors
void JunctionTrack::disconnectFromNeighbours() {
    disconnectFront();
    disconnectRear();
}

void JunctionTrack::disconnectFront() {
    m_forwardJunction.removeAllBranches();
}

void JunctionTrack::disconnectRear() {
    m_rearJunction.removeAllBranches();
}

// branching
bool JunctionTrack::selectForwardBranch(ITrackSegment* track) {
    bool result = m_forwardJunction.selectBranch(track);
    updateSignals();
    return result;
}

bool JunctionTrack::selectForwardBranchById(unsigned int id) {
    bool result = m_forwardJunction.selectBranchById(id);
    updateSignals();
    return result;
}

bool JunctionTrack::selectRearBranch(ITrackSegment* track) {
    bool result = m_rearJunction.selectBranch(track);
    updateSignals();
    return result;
}

bool JunctionTrack::selectRearBranchById(unsigned int id) {
    bool result = m_rearJunction.selectBranchById(id);
    updateSignals();
    return result;
}

void JunctionTrack::checkCollisions() {
    ITrackSegment* rearBranch = getSelectedRearEnd();
    ITrackSegment* forwardBranch = getSelectedForwardEnd();
    if(CollisionChecker::collisionWillOccur(rearBranch, forwardBranch)) {
        track_sensor_data rearData = rearBranch->getFrontSensor()->getSensorData();
        track_sensor_data frontData = forwardBranch->getRearSensor()->getSensorData();

        bool needToRedirectRearTrain = false;
        bool needToRedirectFrontTrain = false;
        float rearTime = 0;
        float frontTime = 0;

        if(rearData.trainSpeed > 0) {
            float rearDistance = rearData.positionOnTrack - rearBranch->getLength();
            rearTime = fabs(rearDistance / rearData.trainSpeed);
            needToRedirectRearTrain = true;
        }
        if(frontData.trainSpeed < 0) {
            needToRedirectFrontTrain = true;
            float frontDistance = frontData.positionOnTrack;
            frontTime = fabs(frontDistance / frontData.trainSpeed);
        }

        if(needToRedirectFrontTrain && needToRedirectRearTrain) {
            if(frontTime < rearTime) {

            }
        } else if (needToRedirectFrontTrain) {

        } else if (needToRedirectRearTrain) {

        }
    }
}


// most viable - track doesn't have a train
// 2nd most viable - track has train, but will result in longest time before collision
int JunctionTrack::mostViableForwardBranchNumber() {
    int winningBranch = 0;
    float winningTimeTillCollision = 0;
    float winningBranchLength = getLength();
    bool winningBranchHasCollision = true;

    for (int i = 0; i < m_forwardJunction.getBranches().size(); i++) {
        ITrackSegment* frontBranch = m_forwardJunction.getBranches().at(i);
        collision_info_t collisionInfo = CollisionChecker::computeCollision(this, frontBranch);

        if(!collisionInfo.collisionWillOccur && winningBranchHasCollision) {
            winningBranch = i;
            winningBranchHasCollision = false;
            winningTimeTillCollision = -1;
            winningBranchLength = frontBranch->getLength();
        } else if (!collisionInfo.collisionWillOccur && !winningBranchHasCollision) {
            if(frontBranch->getLength() > winningBranchLength) {
                winningBranch = i;
                winningBranchHasCollision = false;
                winningTimeTillCollision = -1;
                winningBranchLength = frontBranch->getLength();
            }
        } else if(collisionInfo.collisionWillOccur && winningBranchHasCollision) {
            if(collisionInfo.timeTillCollision > winningTimeTillCollision) {
                winningBranch = i;
                winningBranchHasCollision = true;
                winningTimeTillCollision = collisionInfo.timeTillCollision;
                winningBranchLength = frontBranch->getLength();
            }
        }
    }
    return winningBranch;
}

int JunctionTrack::mostViableRearBranchNumber() {
    return 0;
}
