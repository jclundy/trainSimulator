#include "junctiontrack.h"

JunctionTrack::JunctionTrack(unsigned int id, float length, const QPointF &position, unsigned int maxBranches):
    m_forwardJunction(this, maxBranches),
    m_rearJunction(this, maxBranches)
{
    m_heading = 0;
    m_length = length;
    m_id = id;

    m_forwardPosition.setX(position.x() + length/2);
    m_forwardPosition.setY(position.y());

    m_rearPosition.setX(position.x() - length/2);
    m_rearPosition.setY(position.y());
}

JunctionTrack::~JunctionTrack() {
    disconnectFromNeighbours();
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
float JunctionTrack::getLength() {
    return m_length;
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
QPointF JunctionTrack::getFrontEndPosition() {
    return m_forwardPosition;
}
QPointF JunctionTrack::getRearEndPosition() {
    return m_rearPosition;
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


//getters
unsigned int JunctionTrack::getId() {
    return m_id;
}

QPointF JunctionTrack::getCenter() {
    return m_center;
}

float JunctionTrack::getHeading() {
    return m_heading;
}
