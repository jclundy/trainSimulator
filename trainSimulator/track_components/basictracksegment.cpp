#include "basictracksegment.h"

BasicTrackSegment::BasicTrackSegment(unsigned int id, float length) :
    m_id(id),
    m_frontSensor(0),
    m_rearSensor(length)
{

}

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

}

void BasicTrackSegment::unTriggerSensors(IVehicle *train) {

}
