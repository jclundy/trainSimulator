#include "tracksegment.h"
#include "trackend.h"

// library includes
#include <math.h>

TrackSegment::TrackSegment(float length, const QPointF &position):
    m_forwardEnd(this, TRACK_FRONT),
    m_rearEnd(this, TRACK_REAR)
{
    m_length = length;

    m_forwardEnd.m_position.setX(position.x() + m_length/2);
    m_forwardEnd.m_position.setY(position.y());

    m_rearEnd.m_position.setX(position.x() - m_length/2);
    m_rearEnd.m_position.setY(position.y());
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
    float R = m_length / 2;
    float rads = degrees*M_PI / 180.0;
    float x_offset = R * cos(rads);
    float y_offset = R * sin(rads);

    QPointF offset(x_offset, y_offset);

    m_forwardEnd.m_position = center + offset;
    m_rearEnd.m_position = center - offset;
}

void TrackSegment::setRotationAboutFront(float degrees) {
    float R = m_length;
    float rads = degrees*M_PI / 180.0;
    float x_offset = R * cos(rads);
    float y_offset = R * sin(rads);

    QPointF offset(x_offset, y_offset);
    m_rearEnd.m_position = m_forwardEnd.m_position + offset;
}

void TrackSegment::setRotationAboutRear(float degrees) {
    float R = m_length;
    float rads = degrees*M_PI / 180.0;
    float x_offset = R * cos(rads);
    float y_offset = R * sin(rads);

    QPointF offset(x_offset, y_offset);
    m_forwardEnd.m_position = m_rearEnd.m_position + offset;
}