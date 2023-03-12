#ifndef TRACKSEGMENT_H
#define TRACKSEGMENT_H

#include "trackend.h"

class TrackSegment
{
public:
    TrackSegment(float length, const QPointF &position = QPointF(0,0));
    ~TrackSegment();

    // public methods
    void remove();
    void connectRearToTrack(TrackSegment *track);
    void connectFrontToTrack(TrackSegment *track);

    //getters
    float getLength();
    TrackEnd* getForwardEnd();
    TrackEnd* getRearEnd();
    QPointF getCenter();
    float getHeading();

    // modifiers
    void setCenter(const QPointF &newCenter);
    void translate(const QPointF &offset);
    void setRotationAboutCenter(float degrees);
    void setRotationAboutFront(float degrees);
    void setRotationAboutRear(float degrees);

private:
    float m_length;
    TrackEnd m_forwardEnd;
    TrackEnd m_rearEnd;
};

#endif // TRACKSEGMENT_H
