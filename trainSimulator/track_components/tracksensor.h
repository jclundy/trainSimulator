#ifndef TRACKSENSOR_H
#define TRACKSENSOR_H

#include "train/ivehicle.h"

typedef struct {
    bool trainPresent;
    float trainSpeed;
    int trainId;
    float positionOnTrack; // from track rear
} track_sensor_data;

static const track_sensor_data default_track_sensor_data = {
    .trainPresent = false,
    .trainSpeed = 0,
    .trainId = -1,
    .positionOnTrack = 0
};

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
    track_sensor_data getSensorData();

    // setters
    void reset();
    void trigger(IVehicle *train, float positionOnTrack);
    void unTrigger(IVehicle *train);
    void countDown(float dt);
    void reposition(float position);


private:
    void updateTrainInfo(IVehicle *train, float positionOnTrack);

    float m_positionOnTrack;
    bool m_trainPresent;
    int m_trainId;
    int m_trainPriority;

    float m_trainSpeed;
    float m_trainPositionOnTrack;
    float m_timeoutSetting;
    float m_countDown;
};

#endif // TRACKSENSOR_H
