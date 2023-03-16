#include "junctiontrack.h"

JunctionTrack::JunctionTrack(unsigned int id, float length, const QPointF &position, unsigned int maxBranches):
    m_forwardJunction(this, maxBranches),
    m_rearJunction(this, maxBranches),
    m_trackGeometry(length, position)
{
    m_id = id;

}

JunctionTrack::~JunctionTrack() {
    disconnectFromNeighbours();
}

// ITrackSegment Interface
unsigned int JunctionTrack::getId() {
    return m_id;
}

TrackGeometry* JunctionTrack::getTrackGeometry() {
    return &m_trackGeometry;
}

float JunctionTrack::getLength() {
    return m_trackGeometry.getLength();
}

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
        QPointF delta = track->getTrackGeometry()->getFrontEndPosition() - m_trackGeometry.getRearEndPosition();
        m_trackGeometry.translate(delta);

    } else if (track->isLinear()){
        // this check is required to avoid infinite recursion if track is a junction

        // if our junction already has a connection,
        // update the track's front end position
        track->updateFrontPosition(this);
    } else {
        m_trackGeometry.setRearPosition(track->getTrackGeometry()->getFrontEndPosition());
    }
}

void JunctionTrack::updateFrontPosition(ITrackSegment* track) {
    bool frontWasInitiallyTerminal = m_forwardJunction.getNumBranches() == 1;

    if(frontWasInitiallyTerminal && isRearTerminal()) {
        QPointF delta = track->getTrackGeometry()->getRearEndPosition() - m_trackGeometry.getFrontEndPosition();
        m_trackGeometry.translate(delta);
    } else if (track->isLinear()){
        // this check is required to avoid infinite recursion if track is a junction

        // if our junction already has a connection,
        // update the track's rear end position
        track->updateRearPosition(this);
    } else {
        m_trackGeometry.setForwardPosition(track->getTrackGeometry()->getRearEndPosition());
    }
}

ISignal* JunctionTrack::getFrontSignal() {
    return m_frontSignal;
}

ISignal* JunctionTrack::getRearSignal() {
    return m_rearSignal;
}

bool JunctionTrack::placeFrontSignal(ISignal* signal) {
    if(m_frontSignal== NULL) {
        m_frontSignal = signal;
        return true;
    }
    return false;
}

bool JunctionTrack::placeRearSignal(ISignal* signal) {
    if(m_rearSignal == NULL) {
        m_rearSignal = signal;
        return true;
    }
    return false;
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
    return m_forwardJunction.selectBranch(track);
}

bool JunctionTrack::selectForwardBranchById(unsigned int id) {
    return m_forwardJunction.selectBranchById(id);
}

bool JunctionTrack::selectRearBranch(ITrackSegment* track) {
    return m_rearJunction.selectBranch(track);
}

bool JunctionTrack::selectRearBranchById(unsigned int id) {
    return m_rearJunction.selectBranchById(id);

}
