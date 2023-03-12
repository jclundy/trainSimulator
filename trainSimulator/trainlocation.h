#ifndef TRAINLOCATION_H
#define TRAINLOCATION_H

#include "tracksegment.h"

typedef enum {
    SUCCESS,
    HIT_TERMINAL,
    DERAILED_AT_JUNCTION,
    DERAILED_OFF_TRACK
} train_motion_result;

class TrainLocation
{
public:
    TrainLocation(TrackSegment* track, float position);
    train_motion_result increment(float distance);
private:
    train_motion_result moveToForwardTrack(float distance);
    train_motion_result moveToRearTrack(float distance);
    train_motion_result moveToNextTrack(TrackSegment* track, float distance);

    TrackSegment* m_track;
    float m_positionOnTrack; // measured from track 'rear-end'
};

#endif // TRAINLOCATION_H
