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

typedef struct {
    train_motion_result front, rear;
} train_full_motion_result;

class Train : public IVehicle
{
friend class TrainTest;

public:
    Train(unsigned int id, float length = 5);
    ~Train();
    // getters and setters
    unsigned int getId() override;
    float getSpeed() override;
    float getAcceleration();
    int getPriority() override;
    float getLength();
    TrainLocation getFrontLocation();
    TrainLocation getRearLocation();
    void setPriority(int priority);
    void setLength(float length);
    bool isStopped();
    bool isHalted();
    void unHalt();
    train_motion_result getRailState();

    // initialization
    void place(ITrackSegment* track, float rearPositionOnTrack=0, train_orientation orientation=TRAIN_HEAD_TOWARDS_TRACK_FRONT);
    void slide(float distance);
    void setStartingSpeed(float speed);
    void setControlModel(TrainControlModel *controlModel);
    // control and simulation
    void setDesiredSpeed(float setpoint);
    float getDesiredSpeed();
    bool drive(float dt);
    void stop();
    float getMaxSpeed();
    // train 2D location
    QPointF getLocationInWorld();
    QPointF getFrontLocationInWorld();
    QPointF getRearLocationInWorld();

private:
    // private methods
    void triggerSensors();
    void unTriggerSensors();
    train_full_motion_result move(float positionDelta);

    // private members
    unsigned int m_id;
    int m_priority;
    float m_speed; // relative to track
    float m_acceleration;
    float m_speedSetpoint;

    float m_length;
    bool m_isDriving;
    bool m_isHalted;

    TrainControlModel *m_controlModel;
    train_motion_result m_railState;

    TrainLocation m_frontLocation;
    TrainLocation m_rearLocation;
};

#endif // TRAIN_H
