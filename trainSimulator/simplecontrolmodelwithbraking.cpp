#include "simplecontrolmodelwithbraking.h"
#include <math.h>

SimpleControlModelWithBraking::SimpleControlModelWithBraking(float maxSpeed, float maxAcceleration, float maxBraking, float errorThreshold)
{
    m_maxSpeed = maxSpeed;
    m_maxAcceleration = maxAcceleration;
    m_maxBraking = maxBraking;
    m_errorThreshold = errorThreshold;
}

void SimpleControlModelWithBraking::computeNewStates(float &speed, float &acceleration, float speedSetpoint, float dt) {
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
    // situation where we are braking - speed and setpoint are same sign
    else if((speedSetpoint < speed) && (speedSetpoint > 0 && speed > 0)) {
        acceleration = -m_maxBraking;
    } else if ((speedSetpoint > speed) && (speedSetpoint < 0 && speed < 0)) {
        acceleration = m_maxBraking;
    }
    // situation where engine is driving
    else {
        acceleration = m_maxAcceleration * copysign(1.0, setpointError);
    }
    // update speed
    speed = speed + dt*acceleration;
}
