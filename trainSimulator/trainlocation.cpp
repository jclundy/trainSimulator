#include "trainlocation.h"
#include <math.h>

TrainLocation::TrainLocation()
{
    m_state = DERAILED_OFF_TRACK;
    m_track = NULL;
    m_positionOnTrack = 0;
}

train_motion_result TrainLocation::resetPosition(TrackSegment* track, float newPosition) {
    m_track = track;
    m_positionOnTrack = 0;
    m_state = SUCCESS;

    // this will handle case when placing a train that is longer then a track segment
    float delta = newPosition;
    m_state = increment(delta);
    return m_state;
}

train_motion_result TrainLocation::increment(float delta) {
    float newPosition = m_positionOnTrack + delta;
    train_motion_result result = SUCCESS;
    if(delta > 0) {
        if(newPosition < m_track->getLength()) {
            m_positionOnTrack = newPosition;
            result = SUCCESS;
        } else {
            float overshoot = newPosition - m_track->getLength();
            result = moveToForwardTrack(overshoot);
        }
    } else { // delta < 0
        if(newPosition > 0) {
            m_positionOnTrack = newPosition;
            result = SUCCESS;
        } else {
            float overshoot = newPosition;
            result = moveToRearTrack(overshoot);
        }
    }
    return result;
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
        m_track = m_track->getForwardEnd()->getSelectedTrackSegment();
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
        m_track = m_track->getRearEnd()->getSelectedTrackSegment();
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

train_motion_result TrainLocation::getState() {
    return m_state;
}

float TrainLocation::getPositionOnTrack() {
    return m_positionOnTrack;
}

QPointF TrainLocation::getPositionInWorld() {
    float R = m_positionOnTrack; // measured from track 'rear-end'
    float heading_rads = m_track->getHeading() * M_PI / 180.0;

    float x = m_track->getRearEnd()->m_position.x() + cos(heading_rads) * R;
    float y = m_track->getRearEnd()->m_position.y() + sin(heading_rads) * R;

    return QPointF(x,y);
}

unsigned int TrainLocation::getTrackId() {
    return m_track->getId();
}
