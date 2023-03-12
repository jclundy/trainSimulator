#ifndef TRAIN_H
#define TRAIN_H

#include "tracksegment.h"

class TrainLocation;

class Train
{
public:
    Train();
    void place(TrackSegment* track, bool forward);
    void drive();
    void setDirection();
    void stop();

private:
    int direction; // -1 reverse, 0 neutral, 1 forward
    float m_speed;
    float m_acceleration;
    float m_length;

    TrainLocation frontLocation;
    TrainLocation rearLocation;
};

#endif // TRAIN_H
