#include "lineartrack.h"

// library includes
#include <math.h>

LinearTrack::LinearTrack(unsigned int id, float length, const QPointF &position)
{
    m_id = id;
    m_rearTrack = NULL;
    m_forwardTrack = NULL;
    m_trackGeometry = TrackGeometry(length, position);
}

LinearTrack::~LinearTrack() {
    disconnectBothEnds();
}

unsigned int LinearTrack::getId() {
    return m_id;
}

TrackGeometry* LinearTrack::getTrackGeometry() {
    return &m_trackGeometry;
}

track_segment_type LinearTrack::getType() {
    return LINEAR_TRACK;
}

bool LinearTrack::isJunction() {
    return false;
}

bool LinearTrack::isLinear() {
    return false;
}

ITrackSegment* LinearTrack::getSelectedForwardEnd() {
    return m_forwardTrack;
}

ITrackSegment* LinearTrack::getSelectedRearEnd() {
    return m_rearTrack;
}

QList<ITrackSegment*> LinearTrack::getForwardNeighbours() {
    QList<ITrackSegment*> list;
    if(m_forwardTrack != NULL) {
        list.append(m_forwardTrack);
    }
    return list;
}

QList<ITrackSegment*> LinearTrack::getRearNeighbours() {
    QList<ITrackSegment*> list;
    if(m_rearTrack != NULL) {
        list.append(m_rearTrack);
    }
    return list;
}

bool LinearTrack::connectRearToTrack(ITrackSegment *track) {
    if(track->isLinear()) {
        return connectRearToTrack((LinearTrack *) track);
    } else {
        // TODO - implement this after implementing TrackJunction class
        return false;
    }
}

bool LinearTrack::connectFrontToTrack(ITrackSegment *track) {
    if(track->isLinear()) {
        return connectFrontToTrack((LinearTrack *) track);
    } else {
        // TODO - implement this after implementing TrackJunction class
        return false;
    }
}

void LinearTrack::disconnectFromTrackSegment(ITrackSegment *track) {
    if(track == m_forwardTrack) {
        m_forwardTrack = NULL;
    }
    if(track == m_rearTrack) {
        m_rearTrack = NULL;
    }
}

void LinearTrack::disconnectBothEnds() {
    disconnectFront();
    disconnectRear();
}

void LinearTrack::disconnectFront() {
    m_forwardTrack->disconnectFromTrackSegment(this);
    m_forwardTrack = NULL;
}

void LinearTrack::disconnectRear() {
    m_rearTrack->disconnectFromTrackSegment(this);
    m_rearTrack = NULL;
}

bool LinearTrack::connectRearToTrack(LinearTrack *track) {
    // to keep things simple, make sure both ends are terminals
    if(isRearTerminal() == false || track->isFrontTerminal() == false) {
        return false;
    }

    m_rearTrack = track;
    track->m_forwardTrack = this;
    // if front end is not fixed
    if(isFrontTerminal()) {
        QPointF delta = track->getFrontEndPosition() - m_lineSegment.p2();
        translate(delta);
    } else {
        // leave front end in place, modify track length
        setRearPosition(track->getFrontEndPosition());
    }
    return true;
}

bool LinearTrack::connectFrontToTrack(LinearTrack *track) {

    // to keep things simple, make sure our front end is a terminal
    if(isFrontTerminal() == false || track->isRearTerminal() == false) {
        return false;
    }

    m_forwardTrack = track;
    track->m_rearTrack = this;

    // if rear end is not fixed
    if(isRearTerminal()) {
        QPointF delta = track->getRearEndPosition() - getFrontEndPosition();
        translate(delta);
    } else {
        // leave front end in place, modify track length
        setForwardPosition(track->getRearEndPosition());
    }
    return true;
}

bool LinearTrack::isFrontTerminal() {
    return m_forwardTrack == NULL;
}

bool LinearTrack::isRearTerminal() {
    return m_rearTrack == NULL;
}
