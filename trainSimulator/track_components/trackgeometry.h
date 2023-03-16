#ifndef TRACKGEOMETRY_H
#define TRACKGEOMETRY_H

#include <QPointF>
#include <QLineF>

class TrackGeometry
{
public:
    TrackGeometry(float length, const QPointF &position);

    //getters
    QPointF getFrontEndPosition();
    QPointF getRearEndPosition();
    float getLength();
    float getHeading();
    QPointF getCenter();
    QLineF getLine();

    // modifiers
    void setCenter(const QPointF &newCenter);
    void translate(const QPointF &offset);
    void setRotationAboutCenter(float degrees);
    void setRotationAboutFront(float degrees);
    void setRotationAboutRear(float degrees);
    void setForwardPosition(QPointF position);
    void setRearPosition(QPointF position);
    void translateForwardPosition(QPointF position);
    void translateRearPosition(QPointF position);
private:
    // public members
    QLineF m_lineSegment;
};

#endif // TRACKGEOMETRY_H
