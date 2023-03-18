#include "basictracksegment.h"

unsigned int BasicTrackSegment::getId() {
    return m_id;
}

float BasicTrackSegment::getLength() {
    return m_trackGeometry->getLength();
}

TrackGeometry* BasicTrackSegment::getTrackGeometry() {
    return m_trackGeometry;
}

ISignal* BasicTrackSegment::getFrontSignal() {
    return m_frontSignal;
}

ISignal* BasicTrackSegment::getRearSignal() {
    return m_rearSignal;
}

bool BasicTrackSegment::placeFrontSignal(ISignal* signal) {
    if(m_frontSignal== NULL) {
        m_frontSignal = signal;
        return true;
    }
    return false;
}

bool BasicTrackSegment::placeRearSignal(ISignal* signal) {
    if(m_rearSignal == NULL) {
        m_rearSignal = signal;
        return true;
    }
    return false;
}

void BasicTrackSegment::updateSignals() {
    if(m_frontSignal != NULL) {
        m_frontSignal->update();
    }
    if(m_rearSignal != NULL) {
        m_rearSignal->update();
    }
}


void BasicTrackSegment::triggerSensors(IVehicle *train, float positionOnTrack) {

    if(m_frontSensor != NULL) {

        // the track length can change after initialization.
        // this call ensures the front sensor is at the front of the track
        m_frontSensor->reposition(getTrackGeometry()->getLength());

        m_frontSensor->trigger(train, positionOnTrack);
    }
    if(m_rearSensor != NULL) {
        m_rearSensor->trigger(train, positionOnTrack);
    }
    updateSignals();

}

void BasicTrackSegment::unTriggerSensors(IVehicle *train) {
    if(m_frontSensor != NULL) {
        m_frontSensor->unTrigger(train);
    }
    if(m_rearSensor != NULL) {
        m_rearSensor->unTrigger(train);
    }
    updateSignals();
}

TrackSensor* BasicTrackSegment::getFrontSensor() {
    return m_frontSensor;
}

TrackSensor* BasicTrackSegment::getRearSensor() {
    return m_rearSensor;
}
