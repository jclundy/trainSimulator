#include "lineartrack.h"

// library includes
#include <math.h>

LinearTrack::LinearTrack(unsigned int id, float length, const QPointF &position):
    m_forwardEnd(this, TRACK_FRONT),
    m_rearEnd(this, TRACK_REAR)
{
    m_id = id;

    m_forwardEnd.m_position.setX(position.x() + length/2);
    m_forwardEnd.m_position.setY(position.y());

    m_rearEnd.m_position.setX(position.x() - length/2);
    m_rearEnd.m_position.setY(position.y());
}

LinearTrack::~LinearTrack() {
    disconnectFromNeighbours();
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
    QPointF diff = m_forwardEnd.m_position - m_rearEnd.m_position;
    return sqrt(pow(diff.x(),2) + pow(diff.y(),2));
}

ITrackSegment* LinearTrack::getSelectedForwardEnd() {
    return &m_forwardEnd;
}

ITrackSegment* LinearTrack::getSelectedRearEnd() {
    return &m_rearEnd;
}

QList<ITrackSegment*> LinearTrack::getForwardNeighbours() {
    // TODO - implement this after simplifying TrackEnd class
    QList<ITrackSegment*> list;
    return list;
}

QList<ITrackSegment*> LinearTrack::getRearNeighbours() {
    // TODO - implement this after simplifying TrackEnd class
    QList<ITrackSegment*> list;
    return list;
}

QPointF LinearTrack::getFrontEndPosition() {
    return m_forwardEnd.m_position;
}

QPointF LinearTrack::getRearEndPosition() {
    return m_rearEnd.m_position;
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

void LinearTrack::disconnectFromNeighbours() {
    m_forwardEnd.disconnectAll();
    m_rearEnd.disconnectAll();
}

bool LinearTrack::connectRearToTrack(LinearTrack *track) {
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

bool LinearTrack::connectFrontToTrack(LinearTrack *track) {

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

unsigned int LinearTrack::getId() {
    return m_id;
}

QPointF LinearTrack::getCenter() {
   return (m_forwardEnd.m_position + m_rearEnd.m_position) / 2.0;
}

float LinearTrack::getHeading() {
    QPointF diff = m_forwardEnd.m_position - m_rearEnd.m_position;
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
    m_forwardEnd.m_position += offset;
    m_rearEnd.m_position += offset;
}

void LinearTrack::setRotationAboutCenter(float degrees) {
    QPointF center = getCenter();
    float R = getLength() / 2;
    float rads = degrees*M_PI / 180.0;
    float x_offset = R * cos(rads);
    float y_offset = R * sin(rads);

    QPointF offset(x_offset, y_offset);

    m_forwardEnd.m_position = center + offset;
    m_rearEnd.m_position = center - offset;
}

void LinearTrack::setRotationAboutFront(float degrees) {
    float R = getLength();
    float rads = degrees*M_PI / 180.0;
    float x_offset = R * cos(rads);
    float y_offset = R * sin(rads);

    QPointF offset(x_offset, y_offset);
    m_rearEnd.m_position = m_forwardEnd.m_position + offset;
}

void LinearTrack::setRotationAboutRear(float degrees) {
    float R = getLength();
    float rads = degrees*M_PI / 180.0;
    float x_offset = R * cos(rads);
    float y_offset = R * sin(rads);

    QPointF offset(x_offset, y_offset);
    m_forwardEnd.m_position = m_rearEnd.m_position + offset;
}
