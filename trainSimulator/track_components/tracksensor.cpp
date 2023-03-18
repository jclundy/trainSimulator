#include "tracksensor.h"

#include <math.h>

TrackSensor::TrackSensor(float positionOnTrack, float timeout)
{
    m_positionOnTrack = positionOnTrack;
    m_timeoutSetting = timeout; // seconds
    reset();
}

bool TrackSensor::isTrainPresent()
{
    return m_trainPresent;
}

int TrackSensor::getTrainId()
{
    return m_trainId;
}

int TrackSensor::getTrainPriority()
{
    return m_trainPriority;
}

float TrackSensor::getTrainSpeed()
{
    return m_trainSpeed;
}

float TrackSensor::getTrainPositionOnTrack()
{
    return m_trainPositionOnTrack;
}

track_sensor_data TrackSensor::getSensorData() {
    track_sensor_data sensorData = default_track_sensor_data;
    sensorData.trainPresent = m_trainPresent;
    sensorData.trainId = m_trainId;
    sensorData.trainSpeed = m_trainSpeed;
    sensorData.positionOnTrack = m_positionOnTrack;
    return sensorData;
}


void TrackSensor::reset()
{
    m_trainId = -1;
    m_trainPresent = false;
    m_trainPriority = 0;
    m_trainPositionOnTrack = 0;
    m_countDown = 0;
}

void TrackSensor::trigger(IVehicle *train, float positionOnTrack)
{
    // reset countdown
    m_countDown = m_timeoutSetting;
    m_trainPresent = true;

    if (isTrainPresent() == false)
    {
        // if no train previously present, just trigger the sensor
        updateTrainInfo(train, positionOnTrack);
    }
    else if (m_trainId == (int)train->getId())
    {
        // if it is the same train as before keep triggering the sensor
        updateTrainInfo(train, positionOnTrack);
    }
    else
    {
        float currentDistanceToSensor = m_trainPositionOnTrack - m_positionOnTrack;
        float otherTrainsDistanceToSensor = positionOnTrack - m_positionOnTrack;

        if (fabs(currentDistanceToSensor) > fabs(otherTrainsDistanceToSensor))
        {
            updateTrainInfo(train, positionOnTrack);
        }
    }
}

void TrackSensor::unTrigger(IVehicle *train)
{
    if (m_trainId == (int) train->getId())
    {
        reset();
    }
}

void TrackSensor::reposition(float position) {
    m_positionOnTrack = position;
}


void TrackSensor::updateTrainInfo(IVehicle *train, float positionOnTrack)
{
    m_trainId = train->getId();
    m_trainPriority = train->getPriority();
    m_trainSpeed = train->getSpeed();
    m_trainPositionOnTrack = positionOnTrack;
}
