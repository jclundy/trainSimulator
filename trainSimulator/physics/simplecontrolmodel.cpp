#include "simplecontrolmodel.h"
#include <math.h>

SimpleControlModel::SimpleControlModel(float maxSpeed, float maxAcceleration, float errorThreshold)
{
    m_maxSpeed = maxSpeed;
    m_maxAcceleration = maxAcceleration;
    m_errorThreshold = errorThreshold;
}

void SimpleControlModel::computeNewStates(float &speed, float &acceleration, float speedSetpoint, float dt) {
    // if speed is greater than max speed, slow it down
    if(speedSetpoint > m_maxSpeed) {
        speedSetpoint = m_maxSpeed;
    }

    float setpointError = (speedSetpoint - speed);

    // if we are at our setpoint speed, stop accelerating
    if(fabs(setpointError) < m_errorThreshold) {
        acceleration = 0;
        speed = speedSetpoint;
    }
    // situation where engine is driving
    else {
        acceleration = m_maxAcceleration * copysign(1.0, setpointError);
    }
    // update speed
    speed = speed + dt*acceleration;
}

float SimpleControlModel::getMaxSpeed() {
    return m_maxSpeed;
}


