#include "junctiontrack.h"

JunctionTrack::JunctionTrack(unsigned int id, float length, const QPointF &position, unsigned int maxBranches):
m_forwardJunction(this, maxBranches),
m_rearJunction(this, maxBranches)
{
    m_center = position;
    m_heading = 0;
    m_length = length;
    m_id = id;
}

JunctionTrack::~JunctionTrack() {

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
    return NULL;
}
ITrackSegment* JunctionTrack::getSelectedRearEnd() {
    return NULL;
}
QList<ITrackSegment*> JunctionTrack::getForwardNeighbours() {
    QList<ITrackSegment*> list;
    return list;
}
QList<ITrackSegment*> JunctionTrack::getRearNeighbours() {
    QList<ITrackSegment*> list;
    return list;
}
QPointF JunctionTrack::getFrontEndPosition() {
    return QPointF(0,0);
}
QPointF JunctionTrack::getRearEndPosition() {
    return QPointF(0,0);
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
