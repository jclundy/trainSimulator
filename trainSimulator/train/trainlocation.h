#ifndef TRAINLOCATION_H
#define TRAINLOCATION_H

#include "track_components/lineartrack.h"

typedef enum {
    SUCCESS,
    HIT_TERMINAL,
    DERAILED_AT_JUNCTION,
    DERAILED_OFF_TRACK
} train_motion_result;

class TrainTest;

class TrainLocation
{
friend class TrainTest;
public:
    TrainLocation();
    train_motion_result resetPosition(ITrackSegment* track, float position);
    train_motion_result increment(float delta);
    train_motion_result getState();
    float getPositionOnTrack();
    QPointF getPositionInWorld();
    unsigned int getTrackId();

private:
    train_motion_result moveToForwardTrack(float delta);
    train_motion_result moveToRearTrack(float delta);

    ITrackSegment* m_track;
    train_motion_result m_state;
    float m_positionOnTrack; // measured from track 'rear-end'
};

#endif // TRAINLOCATION_H
