#include "tracksegment.h"
#include "trackend.h"

// library includes
#include <math.h>

TrackSegment::TrackSegment(float length, const QPointF &position):
    m_forwardEnd(this, TRACK_FRONT),
    m_rearEnd(this, TRACK_REAR)
{
    m_forwardEnd.m_position.setX(position.x() + length/2);
    m_forwardEnd.m_position.setY(position.y());

    m_rearEnd.m_position.setX(position.x() - length/2);
    m_rearEnd.m_position.setY(position.y());
}

TrackSegment::~TrackSegment() {
    disconnectFromNeighbours();
}

void TrackSegment::disconnectFromNeighbours() {
    m_forwardEnd.disconnectAll();
    m_rearEnd.disconnectAll();
}

bool TrackSegment::connectRearToTrack(TrackSegment *track) {
    // to keep things simple, make sure our rear end is a terminal
    if(m_rearEnd.isTerminal() == false) {
        return false;
    }

    bool success = m_rearEnd.connectTo(track->getForwardEnd());
    if(success) {
        // if front end is not fixed
        if(m_forwardEnd.isTerminal()) {
            QPointF delta = track->getForwardEnd()->m_position - m_rearEnd.m_position;
            translate(delta);
        } else {
            // leave front end in place, modify track length
            m_rearEnd.m_position = track->getForwardEnd()->m_position;
        }
    }
    return success;
}

bool TrackSegment::connectFrontToTrack(TrackSegment *track) {

    // to keep things simple, make sure our front end is a terminal
    if(m_forwardEnd.isTerminal() == false) {
        return false;
    }

    bool success = m_forwardEnd.connectTo(track->getRearEnd());

    if(success) {
        // if rear end is not fixed
        if(m_rearEnd.isTerminal()) {
            QPointF delta = track->getRearEnd()->m_position - m_forwardEnd.m_position;
            translate(delta);
        } else {
            // leave front end in place, modify track length
            m_forwardEnd.m_position = track->getRearEnd()->m_position;
        }
    }
    return success;
}

float TrackSegment::getLength() {
    QPointF diff = m_forwardEnd.m_position - m_rearEnd.m_position;
    return sqrt(pow(diff.x(),2) + pow(diff.y(),2));
}

TrackEnd* TrackSegment::getForwardEnd() {
    return &m_forwardEnd;
}

TrackEnd* TrackSegment::getRearEnd() {
    return &m_rearEnd;
}

QPointF TrackSegment::getCenter() {
   return (m_forwardEnd.m_position + m_rearEnd.m_position) / 2.0;
}

float TrackSegment::getHeading() {
    QPointF diff = m_forwardEnd.m_position - m_rearEnd.m_position;
    return atan2(diff.y(), diff.x()) * 180.0 / M_PI;
}

void TrackSegment::setCenter(const QPointF &newCenter) {
    QPointF offset = newCenter - getCenter();
    translate(offset);
}

void TrackSegment::translate(const QPointF &offset) {
    m_forwardEnd.m_position += offset;
    m_rearEnd.m_position += offset;
}

void TrackSegment::setRotationAboutCenter(float degrees) {
    QPointF center = getCenter();
    float R = getLength() / 2;
    float rads = degrees*M_PI / 180.0;
    float x_offset = R * cos(rads);
    float y_offset = R * sin(rads);

    QPointF offset(x_offset, y_offset);

    m_forwardEnd.m_position = center + offset;
    m_rearEnd.m_position = center - offset;
}

void TrackSegment::setRotationAboutFront(float degrees) {
    float R = getLength();
    float rads = degrees*M_PI / 180.0;
    float x_offset = R * cos(rads);
    float y_offset = R * sin(rads);

    QPointF offset(x_offset, y_offset);
    m_rearEnd.m_position = m_forwardEnd.m_position + offset;
}

void TrackSegment::setRotationAboutRear(float degrees) {
    float R = getLength();
    float rads = degrees*M_PI / 180.0;
    float x_offset = R * cos(rads);
    float y_offset = R * sin(rads);

    QPointF offset(x_offset, y_offset);
    m_forwardEnd.m_position = m_rearEnd.m_position + offset;
}
