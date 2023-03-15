#include "lineartrack.h"

// library includes
#include <math.h>

LinearTrack::LinearTrack(unsigned int id, float length, const QPointF &position)
{
    m_id = id;
    m_rearTrack = NULL;
    m_forwardTrack = NULL;

    m_forwardPosition.setX(position.x() + length/2);
    m_forwardPosition.setY(position.y());

    m_rearPosition.setX(position.x() - length/2);
    m_rearPosition.setY(position.y());
}

LinearTrack::~LinearTrack() {
    disconnectBothEnds();
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

float LinearTrack::getLength() {
    QPointF diff = m_forwardPosition - m_rearPosition;
    return sqrt(pow(diff.x(),2) + pow(diff.y(),2));
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

QPointF LinearTrack::getFrontEndPosition() {
    return m_forwardPosition;
}

QPointF LinearTrack::getRearEndPosition() {
    return m_rearPosition;
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
        QPointF delta = track->getFrontEndPosition() - m_rearPosition;
        translate(delta);
    } else {
        // leave front end in place, modify track length
        m_rearPosition = track->getFrontEndPosition();
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
        QPointF delta = track->getRearEndPosition() - m_forwardPosition;
        translate(delta);
    } else {
        // leave front end in place, modify track length
        m_forwardPosition = track->getRearEndPosition();
    }
    return true;
}

unsigned int LinearTrack::getId() {
    return m_id;
}

QPointF LinearTrack::getCenter() {
   return (m_forwardPosition + m_rearPosition) / 2.0;
}

float LinearTrack::getHeading() {
    QPointF diff = m_forwardPosition - m_rearPosition;
    return atan2(diff.y(), diff.x()) * 180.0 / M_PI;
}

bool LinearTrack::isFrontTerminal() {
    return m_forwardTrack == NULL;
}

bool LinearTrack::isRearTerminal() {
    return m_rearTrack == NULL;
}

void LinearTrack::setCenter(const QPointF &newCenter) {
    QPointF offset = newCenter - getCenter();
    translate(offset);
}

void LinearTrack::translate(const QPointF &offset) {
    m_forwardPosition += offset;
    m_rearPosition += offset;
}

void LinearTrack::setRotationAboutCenter(float degrees) {
    QPointF center = getCenter();
    float R = getLength() / 2;
    float rads = degrees*M_PI / 180.0;
    float x_offset = R * cos(rads);
    float y_offset = R * sin(rads);

    QPointF offset(x_offset, y_offset);

    m_forwardPosition = center + offset;
    m_rearPosition = center - offset;
}

void LinearTrack::setRotationAboutFront(float degrees) {
    float R = getLength();
    float rads = degrees*M_PI / 180.0;
    float x_offset = R * cos(rads);
    float y_offset = R * sin(rads);

    QPointF offset(x_offset, y_offset);
    m_rearPosition = m_forwardPosition + offset;
}

void LinearTrack::setRotationAboutRear(float degrees) {
    float R = getLength();
    float rads = degrees*M_PI / 180.0;
    float x_offset = R * cos(rads);
    float y_offset = R * sin(rads);

    QPointF offset(x_offset, y_offset);
    m_forwardPosition = m_rearPosition + offset;
}
