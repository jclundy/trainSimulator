#ifndef TRACKSEGMENT_H
#define TRACKSEGMENT_H

#include "trackend.h"

class TrainTest;

class TrackSegment
{
friend class TrainTest;
public:
    TrackSegment(unsigned int id, float length = 20, const QPointF &position = QPointF(0,0));
    ~TrackSegment();

    // public methods
    void disconnectFromNeighbours();
    bool connectRearToTrack(TrackSegment *track);
    bool connectFrontToTrack(TrackSegment *track);

    //getters
    unsigned int getId();
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
    unsigned int m_id;
    TrackEnd m_forwardEnd;
    TrackEnd m_rearEnd;
};

#endif // TRACKSEGMENT_H
