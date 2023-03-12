#ifndef TRAIN_H
#define TRAIN_H

#include "tracksegment.h"
#include "trainlocation.h"

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
    // initialization
    void place(TrackSegment* track, train_orientation orientation);
    void setStartingSpeed(float speed);
    // control and simulation
    void setDesiredSpeed();
    void drive(float dt);
    void stop();


private:
    int direction; // -1 reverse, 0 neutral, 1 forward
    float m_speed;
    float m_acceleration;
    float m_length;
    bool m_isDriving;

    TrainLocation frontLocation;
    TrainLocation rearLocation;
};

#endif // TRAIN_H
