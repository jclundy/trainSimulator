#include "trackgeometry.h"

TrackGeometry::TrackGeometry(float length, const QPointF &position)
{
    // front position
    float x1 = position.x() + length/2;
    float y1 = position.y();

    // rear position
    float x2 = position.x() - length/2;
    float y2 = position.y();

    m_lineSegment.setLine(x1, y1, x2, y2);
}

float TrackGeometry::getLength() {
    return m_lineSegment.length();
}

QPointF TrackGeometry::getCenter() {
   return m_lineSegment.center();
}

QLineF TrackGeometry::getLine() {
    return m_lineSegment;
}

float TrackGeometry::getHeading() {
    return m_lineSegment.angle();
}

QPointF TrackGeometry::getFrontEndPosition() {
    return m_lineSegment.p1();
}

QPointF TrackGeometry::getRearEndPosition() {
    return m_lineSegment.p2();
}

void TrackGeometry::setCenter(const QPointF &newCenter) {
    QPointF offset = newCenter - m_lineSegment.center();
    m_lineSegment.translate(offset);
}

void TrackGeometry::translate(const QPointF &offset) {
    m_lineSegment.translate(offset);
}

void TrackGeometry::setRotationAboutCenter(float degrees) {
    m_lineSegment.setAngle(degrees);
}

void TrackGeometry::setRotationAboutFront(float degrees) {

    QPointF oldFront = m_lineSegment.p1();
    m_lineSegment.setAngle(degrees);
    QPointF newFront = m_lineSegment.p1();
    QPointF delta = oldFront - newFront;
    m_lineSegment.translate(delta);
}

void TrackGeometry::setRotationAboutRear(float degrees) {
    QPointF oldRear = m_lineSegment.p2();
    m_lineSegment.setAngle(degrees);
    QPointF newRear = m_lineSegment.p2();
    QPointF delta = oldRear - newRear;
    m_lineSegment.translate(delta);
}

void TrackGeometry::setForwardPosition(QPointF position) {
    m_lineSegment.setP1(position);
}

void TrackGeometry::setRearPosition(QPointF position) {
    m_lineSegment.setP2(position);
}

void TrackGeometry::translateForwardPosition(QPointF position) {
    QPointF delta = position - m_lineSegment.p1();
    translate(delta);
}

void TrackGeometry::translateRearPosition(QPointF position) {
    QPointF delta = position - m_lineSegment.p2();
    translate(delta);
}
