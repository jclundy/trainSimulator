#ifndef ITRACKSEGMENT_H
#define ITRACKSEGMENT_H

#include "trackend.h"

typedef enum {
    LINEAR_TRACK,
    JUCNTION_TRACK
} track_segment_type;

class ITrackSegment
{

public:
virtual ~ITrackSegment() {}
virtual track_segment_type getType() = 0;
virtual bool isJunction() = 0;
virtual bool isLinear() = 0;
virtual float getLength() = 0;

virtual TrackEnd* getSelectedForwardEnd() = 0;
virtual TrackEnd* getSelectedRearEnd() = 0;

virtual QList<ITrackSegment*> getForwardNeighbours() = 0;
virtual QList<ITrackSegment*> getRearNeighbours() = 0;

virtual QPointF getFrontEndPosition() = 0;
virtual QPointF getRearEndPosition() = 0;

virtual bool connectRearToTrack(ITrackSegment *track) = 0;
virtual bool connectFrontToTrack(ITrackSegment *track) = 0;

};

#endif // ITRACKSEGMENT_H
