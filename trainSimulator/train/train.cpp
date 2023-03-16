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
    // front and rear location are initialized by the default TrainLocation constructor

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

TrainLocation Train::getFrontLocation() {
    return frontLocation;
}

TrainLocation Train::getRearLocation() {
    return rearLocation;
}

void Train::setPriority(int priority) {
    m_priority = priority;
}

void Train::setLength(float length) {
    // Don't allow length change if train has been placed on track or is driving
    if(!m_isDriving && !frontLocation.onTrack()) {
        m_length = length;
    }
}

bool Train::isStopped() {
    return m_isDriving == false;
}


/* Initialization */
void Train::place(ITrackSegment *track, train_orientation orientation) {
    if(m_isDriving) {
        qDebug() << "can't re-position train while driving";
        return;
    }

    float midpoint = track->getLength()/2;
    float headPosition = 0;
    float rearPosition = 0;

    if(orientation == TRAIN_HEAD_TOWARDS_TRACK_FRONT) {
        headPosition = midpoint + m_length/2;
        rearPosition = midpoint - m_length/2;
    } else {
        headPosition = midpoint - m_length/2;
        rearPosition = midpoint + m_length/2;
    }

    frontLocation.resetPosition(track, headPosition);
    rearLocation.resetPosition(track, rearPosition);
}

void Train::slide(float distance) {
    if(!m_isDriving) {
        frontLocation.increment(distance);
        rearLocation.increment(distance);
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

bool Train::drive(float dt) {
    m_isDriving = true;

    if(m_controlModel == NULL) {
        m_controlModel = new SimpleControlModel();
        qDebug() << "didn't set control model - creating new simple control model";
    }
    m_controlModel->computeNewStates(m_speed,m_acceleration, m_speedSetpoint, dt);

    float positionDelta = m_speed * dt;
    train_motion_result result1 = frontLocation.increment(positionDelta);
    train_motion_result result2 = rearLocation.increment(positionDelta);
    if(result1 != SUCCESS || result2 != SUCCESS) {
        stop();
        qDebug() << "Train stopped.  Front and rear states: " << result1 << ", " << result2;
    }

    return result1 == SUCCESS && result2 == SUCCESS;
}

void Train::stop() {
    m_isDriving = false;
    m_speedSetpoint = 0;
    m_speed = 0;
}

/* Train 2D location */
QPointF Train::getLocationInWorld() {
    QPointF frontPosition = frontLocation.getPositionInWorld();
    QPointF rearPosition = rearLocation.getPositionInWorld();
    return (frontPosition + rearPosition) / 2;
}

QPointF Train::getFrontLocationInWorld() {
    return frontLocation.getPositionInWorld();
}

QPointF Train::getRearLocationInWorld() {
    return rearLocation.getPositionInWorld();
}
