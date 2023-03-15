#ifndef SIMPLECONTROLMODEL_H
#define SIMPLECONTROLMODEL_H

#include "traincontrolmodel.h"

class SimpleControlModel : public TrainControlModel
{
public:
    SimpleControlModel(float maxSpeed = 4, float maxAcceleration = 1, float errorThreshold = 10e-3);
    void computeNewStates(float &speed, float &acceleration, float speedSetpoint, float dt) override;
private:
    float m_maxSpeed; // m/s
    float m_maxAcceleration; // m/s^2
    float m_errorThreshold;
};

#endif // SIMPLECONTROLMODEL_H
