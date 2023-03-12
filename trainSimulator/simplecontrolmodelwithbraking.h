#ifndef SIMPLECONTROLMODELWITHBRAKING_H
#define SIMPLECONTROLMODELWITHBRAKING_H

#include "traincontrolmodel.h"

class SimpleControlModelWithBraking : public TrainControlModel
{
public:
    SimpleControlModelWithBraking(float maxSpeed = 4, float maxAcceleration = 1, float maxBraking = 2, float errorThreshold = 10e-3);
    void computeNewStates(float &speed, float &acceleration, float speedSetpoint, float dt) override;

private:
    float m_maxSpeed; // m/s
    float m_maxAcceleration; // m/s^2
    float m_maxBraking; // m/s^2
    float m_errorThreshold;
};

#endif // SIMPLECONTROLMODELWITHBRAKING_H
