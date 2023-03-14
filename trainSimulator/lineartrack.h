#ifndef TRACKSEGMENT_H
#define TRACKSEGMENT_H

#include "trackend.h"

class TrainTest;

class LinearTrack
{
friend class TrainTest;
public:
    LinearTrack(unsigned int id, float length = 20, const QPointF &position = QPointF(0,0));
    ~LinearTrack();

    // public methods
    void disconnectFromNeighbours();
    bool connectRearToTrack(LinearTrack *track);
    bool connectFrontToTrack(LinearTrack *track);

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
