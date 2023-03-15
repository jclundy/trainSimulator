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
    if(track->isJunction() || !track->isFrontTerminal()) {
        return false;
    }
    // also ensure track front is a terminal
    if(track->isFrontTerminal() == false) {
        return false;
    }

    bool rearWasInitiallyTerminal = isRearTerminal();
    bool success = m_rearJunction.addBranch(track);
    if(success) {
        // instead of updating junction's position, we update the track's front position
        track->getTrackGeometry()->setForwardPosition(m_trackGeometry.getRearEndPosition());

        if(rearWasInitiallyTerminal) {

            if(isFrontTerminal()) {
                // if both junctions were terminals, move both junctions
                QPointF delta = track->getTrackGeometry()->getFrontEndPosition() - m_trackGeometry.getRearEndPosition();
                m_trackGeometry.translate(delta);
            } else {
                // move rear junction to track's front, leave front junction in place
                m_trackGeometry.setRearPosition(track->getTrackGeometry()->getFrontEndPosition());
            }

        } else {
            // if our junction already has a connection,
            // update the track's front end position
            track->getTrackGeometry()->setForwardPosition(m_trackGeometry.getRearEndPosition());

        }
    }
    return success;
}

bool JunctionTrack::connectFrontToTrack(ITrackSegment *track) {
    // do not allow a junction to be connected to a junction
    if(track->isJunction() || !track->isRearTerminal()) {
        return false;
    }
    // also ensure track rear is a terminal
    if(track->isRearTerminal() == false) {
        return false;
    }

    bool frontWasInitiallyTerminal = isFrontTerminal();

    bool success = m_forwardJunction.addBranch(track);
    if(success) {
        if(frontWasInitiallyTerminal) {

            if(isRearTerminal()) {
                QPointF delta = track->getTrackGeometry()->getRearEndPosition() - m_trackGeometry.getFrontEndPosition();
                m_trackGeometry.translate(delta);
            } else {
                // move front junction to track's rear, leave rear junction in place
                m_trackGeometry.setForwardPosition(track->getTrackGeometry()->getRearEndPosition());
            }

        } else {
            // if our junction already has a connection,
            // update the track's rear end position
            track->getTrackGeometry()->setRearPosition(m_trackGeometry.getFrontEndPosition());
        }
    }
    return success;
}

void JunctionTrack::disconnectFromTrackSegment(ITrackSegment *track) {
    m_forwardJunction.removeBranch(track);
    m_rearJunction.removeBranch(track);
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
