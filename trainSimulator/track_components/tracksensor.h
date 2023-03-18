#ifndef TRACKSENSOR_H
#define TRACKSENSOR_H

#include "train/ivehicle.h"

class TrackSensor
{
public:
    TrackSensor(float positionOnTrack, float timeout = 5);

    // getters
    bool isTrainPresent();
    int getTrainId();
    int getTrainPriority();
    float getTrainSpeed();
    float getTrainPositionOnTrack();

    // setters
    void reset();
    void trigger(IVehicle *train, float positionOnTrack);
    void unTrigger(IVehicle *train);
    void countDown(float dt);
    void reposition(float position);

private:
    void updateTrainInfo(IVehicle *train, float positionOnTrack);

    int m_positionOnTrack;
    bool m_trainPresent;
    int m_trainId;
    int m_trainPriority;

    float m_trainSpeed;
    float m_trainPositionOnTrack;
    float m_timeoutSetting;
    float m_countDown;
};

#endif // TRACKSENSOR_H
