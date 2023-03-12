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

train_motion_result TrainLocation::increment(float delta) {
    float newPosition = m_positionOnTrack + delta;
    if(delta > 0) {
        if(newPosition < m_track->getLength()) {
            m_positionOnTrack = newPosition;
            return SUCCESS;
        } else {
            float overshoot = newPosition - m_track->getLength();
            return moveToForwardTrack(overshoot);
        }
    } else { // delta < 0
        if(newPosition > 0) {
            m_positionOnTrack = newPosition;
            return SUCCESS;
        } else {
            float overshoot = newPosition;
            return moveToRearTrack(overshoot);
        }
    }
}

train_motion_result TrainLocation::moveToForwardTrack(float delta) {
    // 1. check if hit terminal
    if(m_track->getForwardEnd()->isTerminal()) {
        m_positionOnTrack = m_track->getLength();
        return HIT_TERMINAL;
    }
    // 2. check if there is a next track segment
    if(m_track->getForwardEnd()->getSelectedTrackSegment() == NULL) {
        m_positionOnTrack = m_track->getLength();
        return DERAILED_OFF_TRACK;
    }
    // 3. check if the junction is connected both ways
    if(m_track->getForwardEnd()->isConnectedToNeighbourBothWays()) {
        m_track = m_track->getForwardEnd()->m_parentTrackSegment;
        m_positionOnTrack = 0;

        /*
         * Note - this results in recursion
         * need to be careful that the incremented delta
         * is usually shorter than track length
         *
         * However the delta should be decreased every iteration,
         * so the recursion should terminate evenutally
         */
        increment(delta);
        return SUCCESS;
    } else {
        return DERAILED_AT_JUNCTION;
    }
}

train_motion_result TrainLocation::moveToRearTrack(float delta) {
    // 1. check if hit terminal
    if(m_track->getRearEnd()->isTerminal()) {
        m_positionOnTrack = 0;
        return HIT_TERMINAL;
    }
    // 2. check if there is a next track segment
    if(m_track->getRearEnd()->getSelectedTrackSegment() == NULL) {
        m_positionOnTrack = 0;
        return DERAILED_OFF_TRACK;
    }
    // 3. check if the junction is connected both ways
    if(m_track->getRearEnd()->isConnectedToNeighbourBothWays()) {
        m_track = m_track->getRearEnd()->m_parentTrackSegment;
        m_positionOnTrack = m_track->getLength();
        /*
         * Note - this results in recursion
         * need to be careful that the incremented delta
         * is usually shorter than track length
         *
         * However the delta should be decreased every iteration,
         * so the recursion should terminate evenutally
         */
        return increment(delta);
    } else {
        return DERAILED_AT_JUNCTION;
    }
}

