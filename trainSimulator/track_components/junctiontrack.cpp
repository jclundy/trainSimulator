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

track_segment_type JunctionTrack::getType() {
    return JUNCTION_TRACK;
}

bool JunctionTrack::isJunction() {
    return true;
}
bool JunctionTrack::isLinear() {
    return false;
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
    return false;
}
bool JunctionTrack::connectFrontToTrack(ITrackSegment *track) {
    return false;
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


bool JunctionTrack::connectTrackToFront(ITrackSegment *track) {
    return false;
}

bool JunctionTrack::connectTrackToRear(ITrackSegment *track) {
    return false;
}
