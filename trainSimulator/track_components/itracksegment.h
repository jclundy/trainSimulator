#ifndef ITRACKSEGMENT_H
#define ITRACKSEGMENT_H

#include <QList>
#include "trackgeometry.h"

class Signal;
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

virtual void addFrontConnection(ITrackSegment* track) = 0;
virtual void addRearConnection(ITrackSegment* track) = 0;

virtual bool connectRearToTrack(ITrackSegment *track) = 0;
virtual bool connectFrontToTrack(ITrackSegment *track) = 0;
virtual void disconnectFromTrackSegment(ITrackSegment *track) = 0;

virtual void updateRearPosition(ITrackSegment* track) = 0;
virtual void updateFrontPosition(ITrackSegment* track) = 0;

virtual Signal* getFrontSignal() = 0;
virtual Signal* getRearSignal() = 0;
virtual bool placeFrontSignal(Signal* signal) = 0;
virtual bool placeRearSignal(Signal* signal) = 0;

};

#endif // ITRACKSEGMENT_H
