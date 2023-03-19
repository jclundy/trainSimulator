#ifndef TRAINCONTROLMODEL_H
#define TRAINCONTROLMODEL_H


class TrainControlModel
{
public:
    virtual ~TrainControlModel() {}
    virtual void computeNewStates(float &speed, float &acceleration, float speedSetpoint, float dt) = 0;
    virtual float getMaxSpeed()=0;
};

#endif // TRAINCONTROLMODEL_H
