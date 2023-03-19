#include "train.h"
#include "physics/simplecontrolmodel.h"
#include <QDebug>

Train::Train(unsigned int id, float length)
{
    m_id = id;
    m_speed = 0;
    m_speedSetpoint = 0;
    m_acceleration = 0;
    m_length = length;
    m_isDriving = false;
    m_controlModel = NULL;
    m_railState = DERAILED_OFF_TRACK;
    m_isHalted = false;
    // front and rear location are initialized by the default TrainLocation constructor

}

Train::~Train() {
    if(m_controlModel != NULL) {
        delete m_controlModel;
    }
}

/* Basic getters and setters*/
unsigned int Train::getId() {
    return m_id;
}

float Train::getSpeed() {
    return m_speed;
}

float Train::getAcceleration() {
    return m_acceleration;
}

int Train::getPriority() {
    return m_priority;
}

float Train::getLength() {
    return m_length;
}

TrainLocation Train::getFrontLocation() {
    return m_frontLocation;
}

TrainLocation Train::getRearLocation() {
    return m_rearLocation;
}

void Train::setPriority(int priority) {
    m_priority = priority;
}

void Train::setLength(float length) {
    // Don't allow length change if train has been placed on track or is driving
    if(!m_isDriving && !m_frontLocation.onTrack()) {
        m_length = length;
    }
}

bool Train::isStopped() {
    return (m_speed == 0);
}
bool Train::isHalted() {
    return m_isHalted;
}

void Train::unHalt() {
    m_isHalted = false;
}

train_motion_result Train::getRailState() {
    return m_railState;
}

/* Initialization */
void Train::place(ITrackSegment* track, float rearPosition, train_orientation orientation) {

    unTriggerSensors();
    m_isHalted = false;

    if(m_isDriving) {
        qDebug() << "can't re-position train while driving";
        return;
    }

    m_railState = ON_TRACK;
    float headPosition = 0;
    if(orientation == TRAIN_HEAD_TOWARDS_TRACK_FRONT) {
        headPosition = rearPosition + m_length;
    } else {
        headPosition = rearPosition - m_length;
    }

    m_frontLocation.resetPosition(track, headPosition);
    m_rearLocation.resetPosition(track, rearPosition);

    triggerSensors();
}

void Train::slide(float distance) {
    if(!m_isDriving) {
        move(distance);
    }
}

void Train::setStartingSpeed(float speed) {
    if(m_isDriving) {
        qDebug() << "can't reset train speed while driving";
        return;
    }
    m_speed = speed;
    m_speedSetpoint = speed;
}

void Train::setControlModel(TrainControlModel *controlModel) {
    // this assumes all train objects have a unique control model object
    // train object will automatically initialize itself with a control model if none is given
    if(m_controlModel != NULL) {
        delete(m_controlModel);
    }
    m_controlModel = controlModel;
}

void Train::setDesiredSpeed(float setpoint) {
    m_speedSetpoint = setpoint;
}

float Train::getDesiredSpeed() {
    return m_speedSetpoint;
}

bool Train::drive(float dt) {
    m_isDriving = true;
    if(m_isHalted) {
        return false;
    }

    if(m_controlModel == NULL) {
        m_controlModel = new SimpleControlModel();
        qDebug() << "didn't set control model - creating new simple control model";
    }
    m_controlModel->computeNewStates(m_speed,m_acceleration, m_speedSetpoint, dt);

    float positionDelta = m_speed * dt;

    train_full_motion_result motionResult = move(positionDelta);

    if(motionResult.front != ON_TRACK) {
        m_railState = motionResult.front;
    } else if(motionResult.rear != ON_TRACK) {
        m_railState = motionResult.rear;
    }

    if(motionResult.front != ON_TRACK || motionResult.rear != ON_TRACK) {
        stop();
        m_isHalted = true;
        qDebug() << "Train stopped.  Front and rear states: " << motionResult.front << ", " << motionResult.rear;
    }

    return motionResult.front == ON_TRACK && motionResult.rear == ON_TRACK;
}

void Train::stop() {
    m_isDriving = false;
    m_speedSetpoint = 0;
    m_speed = 0;
}

float Train::getMaxSpeed() {
    if(m_controlModel == NULL) {
        m_controlModel = new SimpleControlModel();
        qDebug() << "didn't set control model - creating new simple control model";
    }
    return m_controlModel->getMaxSpeed();
}

/* Train 2D location */
QPointF Train::getLocationInWorld() {
    QPointF frontPosition = m_frontLocation.getPositionInWorld();
    QPointF rearPosition = m_rearLocation.getPositionInWorld();
    return (frontPosition + rearPosition) / 2;
}

QPointF Train::getFrontLocationInWorld() {
    return m_frontLocation.getPositionInWorld();
}

QPointF Train::getRearLocationInWorld() {
    return m_rearLocation.getPositionInWorld();
}

void Train::triggerSensors() {
    ITrackSegment *frontTrack = m_frontLocation.getTrack();
    if(frontTrack != NULL) {
        frontTrack->triggerSensors(this, m_frontLocation.getPositionOnTrack());
    }

    ITrackSegment *rearTrack = m_rearLocation.getTrack();
    if(rearTrack != NULL) {
        rearTrack->triggerSensors(this, m_rearLocation.getPositionOnTrack());
    }

}

void Train::unTriggerSensors() {
    ITrackSegment *frontTrack = m_frontLocation.getTrack();
    if(frontTrack != NULL) {
        frontTrack->unTriggerSensors(this);
    }

    ITrackSegment *rearTrack = m_rearLocation.getTrack();
    if(rearTrack != NULL) {
        rearTrack->unTriggerSensors(this);
    }
}
train_full_motion_result Train::move(float positionDelta) {
    train_full_motion_result result;

    unTriggerSensors();
    result.front = m_frontLocation.increment(positionDelta);
    result.rear = m_rearLocation.increment(positionDelta);
    triggerSensors();

    return result;
}
