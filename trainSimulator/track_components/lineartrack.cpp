#include "lineartrack.h"
// library includes
#include <math.h>

LinearTrack::LinearTrack(unsigned int id, float length, const QPointF &position)
{
    m_id = id;
    m_rearTrack = NULL;
    m_forwardTrack = NULL;
    m_rearSignal = NULL;
    m_frontSignal = NULL;
    m_trackGeometry = new TrackGeometry(length, position);

    m_frontSensor = new TrackSensor(length);
    m_rearSensor = new TrackSensor(0);
}

LinearTrack::~LinearTrack() {
    disconnectBothEnds();
    delete m_trackGeometry;
    delete m_frontSensor;
    delete m_rearSensor;
}

track_segment_type LinearTrack::getType() {
    return LINEAR_TRACK;
}

bool LinearTrack::isJunction() {
    return false;
}

bool LinearTrack::isLinear() {
    return true;
}

bool LinearTrack::isFrontTerminal() {
    return m_forwardTrack == NULL;
}

bool LinearTrack::isRearTerminal() {
    return m_rearTrack == NULL;
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

bool LinearTrack::isConnectedForward() {
    if(isFrontTerminal()) {
        return false;
    }
    return m_forwardTrack->getSelectedRearEnd() == this;
}

bool LinearTrack::isConnectedReverse() {
    if(isRearTerminal()) {
        return false;
    }
    return m_rearTrack->getSelectedForwardEnd() == this;
}

bool LinearTrack::connectRearToTrack(ITrackSegment *track) {
    if(track->isLinear()) {
        return connectRearToTrack((LinearTrack *) track);
    } else {
        return connectRearToTrack((JunctionTrack*) track);
    }
}

bool LinearTrack::connectFrontToTrack(ITrackSegment *track) {
    if(track->isLinear()) {
        return connectFrontToTrack((LinearTrack *) track);
    } else {
        return connectFrontToTrack((JunctionTrack*) track);
    }
}

void LinearTrack::addFrontConnection(ITrackSegment* track) {
    if(m_forwardTrack == NULL) {
        m_forwardTrack = track;
    }
}

void LinearTrack::addRearConnection(ITrackSegment* track) {
    if(m_rearTrack == NULL) {
        m_rearTrack = track;
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
    updateRearPosition(track);
    return true;
}

bool LinearTrack::connectRearToTrack(JunctionTrack *track) {
    if(isRearTerminal() == false) {
        return false;
    }
    bool success = track->connectFrontToTrack(this);
    if(success) {
        updateRearPosition(track);
    }
    return success;
}

bool LinearTrack::connectFrontToTrack(JunctionTrack *track) {

    if(isFrontTerminal() == false) {
        return false;
    }
    bool success = track->connectRearToTrack(this);
    if(success) {
        updateFrontPosition(track);
    }
    return success;

}

bool LinearTrack::connectFrontToTrack(LinearTrack *track) {

    // to keep things simple, make sure our front end is a terminal
    if(isFrontTerminal() == false || track->isRearTerminal() == false) {
        return false;
    }

    m_forwardTrack = track;
    track->m_rearTrack = this;

    updateFrontPosition(track);
    return true;
}

void LinearTrack::updateRearPosition(ITrackSegment* track) {
    // if front end is not fixed
    if(isFrontTerminal()) {
        QPointF delta = track->getTrackGeometry()->getFrontEndPosition() - m_trackGeometry->getRearEndPosition();
        m_trackGeometry->translate(delta);
    } else {
        // leave front end in place, modify track length
        m_trackGeometry->setRearPosition(track->getTrackGeometry()->getFrontEndPosition());
    }
}

void LinearTrack::updateFrontPosition(ITrackSegment* track) {
    // if rear end is not fixed
    if(isRearTerminal()) {
        QPointF delta = track->getTrackGeometry()->getRearEndPosition() - m_trackGeometry->getFrontEndPosition();
        m_trackGeometry->translate(delta);
    } else {
        // leave rear end in place, modify track length
        m_trackGeometry->setForwardPosition(track->getTrackGeometry()->getRearEndPosition());
    }
}
