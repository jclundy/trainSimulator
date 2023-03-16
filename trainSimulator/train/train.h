#ifndef TRAIN_H
#define TRAIN_H

#include "track_components/lineartrack.h"
#include "trainlocation.h"
#include "physics/traincontrolmodel.h"

class TrainTest;

typedef enum {
    TRAIN_HEAD_TOWARDS_TRACK_FRONT,
    TRAIN_HEAD_TOWARDS_TRACK_REAR
} train_orientation;

class Train
{
friend class TrainTest;

public:
    Train(unsigned int id, float length = 5);
    // getters and setters
    unsigned int getId();
    float getSpeed();
    float getAcceleration();
    int getPriority();
    TrainLocation getFrontLocation();
    TrainLocation getRearLocation();
    void setPriority(int priority);
    void setLength(float length);


    // initialization
    void place(ITrackSegment* track, train_orientation orientation=TRAIN_HEAD_TOWARDS_TRACK_FRONT);
    void slide(float distance);
    void setStartingSpeed(float speed);
    void setControlModel(TrainControlModel *controlModel);
    // control and simulation
    void setDesiredSpeed(float setpoint);
    bool drive(float dt);
    void stop();
    // train 2D location
    QPointF getLocationInWorld();
    QPointF getFrontLocationInWorld();
    QPointF getRearLocationInWorld();

private:
    unsigned int m_id;
    int m_priority;
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
