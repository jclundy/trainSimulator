#ifndef BASICTRACKSEGMENT_H
#define BASICTRACKSEGMENT_H

#include "itracksegment.h"
#include "trackgeometry.h"
//#include "tracksensor.h"

class BasicTrackSegment : public ITrackSegment
{
public:
    ~BasicTrackSegment() {}
    unsigned int getId() override;
    float getLength() override;
    TrackGeometry* getTrackGeometry() override;

    ISignal* getFrontSignal() override;
    ISignal* getRearSignal() override;
    bool placeFrontSignal(ISignal* signal) override;
    bool placeRearSignal(ISignal* signal) override;
    void updateSignals() override;

    void triggerSensors(IVehicle *train, float positionOnTrack) override;
    void unTriggerSensors(IVehicle *train) override;

protected:
    unsigned int m_id;
    TrackGeometry m_trackGeometry;

    ISignal * m_frontSignal;
    ISignal * m_rearSignal;

//    TrackSensor m_frontSensor;
//    TrackSensor m_rearSensor;
};

#endif // BASICTRACKSEGMENT_H
