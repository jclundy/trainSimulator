#ifndef TRAIN_H
#define TRAIN_H

#include "lineartrack.h"
#include "trainlocation.h"
#include "traincontrolmodel.h"

class TrainTest;

typedef enum {
    TRAIN_HEAD_TOWARDS_TRACK_FRONT,
    TRAIN_HEAD_TOWARDS_TRACK_REAR
} train_orientation;

class Train
{
friend class TrainTest;

public:
    Train(float length = 5);
    // initialization
    void place(LinearTrack* track, train_orientation orientation=TRAIN_HEAD_TOWARDS_TRACK_FRONT);
    void slide(float distance);
    void setStartingSpeed(float speed);
    void setControlModel(TrainControlModel *controlModel);
    // control and simulation
    void setDesiredSpeed(float setpoint);
    bool drive(float dt);
    void stop();

    QPointF getLocationInWorld();

private:
    int direction; // -1 reverse, 0 neutral, 1 forward
    float m_speed; // relative to track
    float m_acceleration;
    float m_speedSetpoint;

    float m_length;
    bool m_isDriving;

    TrainControlModel *m_controlModel;

    TrainLocation frontLocation;
    TrainLocation rearLocation;
};

#endif // TRAIN_H
