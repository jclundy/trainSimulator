#ifndef BASICTRACKSEGMENT_H
#define BASICTRACKSEGMENT_H

#include "itracksegment.h"

class BasicTrackSegment : public ITrackSegment
{
public:
    ~BasicTrackSegment() {}

    ISignal* getFrontSignal() override;
    ISignal* getRearSignal() override;
    bool placeFrontSignal(ISignal* signal) override;
    bool placeRearSignal(ISignal* signal) override;
    void updateSignals() override;

    void triggerSensors(IVehicle *train, float positionOnTrack) override;
    void unTriggerSensors(IVehicle *train) override;

protected:
    ISignal * m_frontSignal;
    ISignal * m_rearSignal;

};

#endif // BASICTRACKSEGMENT_H
