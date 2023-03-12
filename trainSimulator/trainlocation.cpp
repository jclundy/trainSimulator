#include "trainlocation.h"

TrainLocation::TrainLocation(TrackSegment* track, float position)
{
    m_track = track;
    m_positionOnTrack = position;

    // should do check against track length
    float trackLength = track->getLength();
    if(m_positionOnTrack > trackLength) {
        m_positionOnTrack = trackLength;
    }
    if(m_positionOnTrack < 0) {
        m_positionOnTrack = 0;
    }
}

train_motion_result TrainLocation::increment(float distance) {
    if(distance > 0) {
        if(distance < m_track->getLength()) {
            m_positionOnTrack+= distance;
            return SUCCESS;
        } else {

        }
    }
}

train_motion_result TrainLocation::moveToForwardTrack(float distance) {
    // 1. check if there is a next track segment
    if(m_track->getForwardEnd() == NULL) {
        m_positionOnTrack = m_track->getLength();
        return DERAILED_OFF_TRACK;
    }
    // 2. check if the junction is connected both ways
//    if(m_track->getForwardEnd()->)
    return SUCCESS;
}

train_motion_result TrainLocation::moveToRearTrack(float distance) {
    return SUCCESS;
}

train_motion_result TrainLocation::moveToNextTrack(TrackSegment* track, float distance) {
    return SUCCESS;
}

