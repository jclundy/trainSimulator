#ifndef ITRACKSEGMENT_H
#define ITRACKSEGMENT_H

#include "trackend.h"

class TrainTest;

typedef enum {
    LINEAR_TRACK,
    JUCNTION_TRACK
} track_segment_type;

class ITrackSegment
{
friend class TrainTest;

public:
virtual bool connectRearToTrack(ITrackSegment *track) = 0;
virtual bool connectFrontToTrack(ITrackSegment *track) = 0;
virtual track_segment_type getType() = 0;
virtual bool isJunction();
virtual bool isLinear();
virtual float getLength();

virtual TrackEnd* getSelectedForwardEnd();
virtual TrackEnd* getSelectedRearEnd();

virtual PointF getFrontEndPosition();
virtual PointF getRearEndPosition();

}

#endif // ITRACKSEGMENT_H
