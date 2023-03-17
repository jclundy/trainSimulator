#ifndef ITRACKSEGMENT_H
#define ITRACKSEGMENT_H

#include <QList>
#include "trackgeometry.h"
#include "track_system/isignal.h"
#include "train/ivehicle.h"
typedef enum {
    LINEAR_TRACK,
    JUNCTION_TRACK
} track_segment_type;

class ITrackSegment
{

public:
virtual ~ITrackSegment() {}
virtual unsigned int getId() = 0;
virtual TrackGeometry* getTrackGeometry() = 0;
virtual track_segment_type getType() = 0;
virtual float getLength() = 0;
virtual bool isJunction() = 0;
virtual bool isLinear() = 0;

virtual bool isFrontTerminal() = 0;
virtual bool isRearTerminal() = 0;

virtual ITrackSegment* getSelectedForwardEnd() = 0;
virtual ITrackSegment* getSelectedRearEnd() = 0;

virtual QList<ITrackSegment*> getForwardNeighbours() = 0;
virtual QList<ITrackSegment*> getRearNeighbours() = 0;

virtual bool isConnectedForward() = 0;
virtual bool isConnectedReverse() = 0;

virtual void addFrontConnection(ITrackSegment* track) = 0;
virtual void addRearConnection(ITrackSegment* track) = 0;

virtual bool connectRearToTrack(ITrackSegment *track) = 0;
virtual bool connectFrontToTrack(ITrackSegment *track) = 0;
virtual void disconnectFromTrackSegment(ITrackSegment *track) = 0;

virtual void updateRearPosition(ITrackSegment* track) = 0;
virtual void updateFrontPosition(ITrackSegment* track) = 0;

virtual ISignal* getFrontSignal() = 0;
virtual ISignal* getRearSignal() = 0;
virtual bool placeFrontSignal(ISignal* signal) = 0;
virtual bool placeRearSignal(ISignal* signal) = 0;
virtual void updateSignals() = 0;

virtual void triggerSensors(IVehicle *train, float positionOnTrack) = 0;
virtual void unTriggerSensors(IVehicle *train) = 0;
};

#endif // ITRACKSEGMENT_H
