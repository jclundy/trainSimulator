#ifndef TRAIN_H
#define TRAIN_H

#include "tracksegment.h"

class TrainLocation;

typedef enum {
    TRACK_FORWARD,
    TRACK_REVERSE
} train_direction;

typedef enum {
    TRAIN_HEAD_TOWARDS_TRACK_FRONT,
    TRAIN_HEAD_TOWARDS_TRACK_REAR
} train_orientation;

class Train
{
public:
    Train(float length = 5);
    void place(TrackSegment* track, train_orientation orientation);
    void drive();
    void setDirection();
    void stop();
    void setSpeed();

private:
    int direction; // -1 reverse, 0 neutral, 1 forward
    float m_speed;
    float m_acceleration;
    float m_length;

    TrainLocation frontLocation;
    TrainLocation rearLocation;
};

#endif // TRAIN_H
