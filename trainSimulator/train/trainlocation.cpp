#include "trainlocation.h"
#include "track_components/itracksegment.h"
#include <math.h>

#include <QDebug>

TrainLocation::TrainLocation()
{
    m_state = DERAILED_OFF_TRACK;
    m_track = NULL;
    m_positionOnTrack = 0;
}

train_motion_result TrainLocation::resetPosition(ITrackSegment* track, float newPosition) {
    m_track = track;
    m_positionOnTrack = 0;
    m_state = ON_TRACK;

    // this will handle case when placing a train that is longer then a track segment
    float delta = newPosition;
    m_state = increment(delta);
    return m_state;
}

train_motion_result TrainLocation::increment(float delta) {

    if(m_track == NULL) {
        m_state = DERAILED_OFF_TRACK;
        return m_state;
    }

    float newPosition = m_positionOnTrack + delta;
    train_motion_result result = ON_TRACK;
    if(delta > 0) {
        if(newPosition < m_track->getLength()) {
            m_positionOnTrack = newPosition;
            result = ON_TRACK;
        } else {
            float overshoot = newPosition - m_track->getLength();
            qDebug() << "moving to forward track with overshoot " << overshoot;

            result = moveToForwardTrack(overshoot);
        }
    } else { // delta < 0
        if(newPosition > 0) {
            m_positionOnTrack = newPosition;
            result = ON_TRACK;
        } else {
            float overshoot = newPosition;
            result = moveToRearTrack(overshoot);
        }
    }
    return result;
}

train_motion_result TrainLocation::moveToForwardTrack(float delta) {
    if(m_track == NULL) {
        m_state = DERAILED_OFF_TRACK;
        return m_state;
    }
    // 1. check if hit terminal
    if(m_track->isFrontTerminal()) {

        qDebug() << "Hit terminal";

        m_positionOnTrack = m_track->getLength();
        return HIT_TERMINAL;
    }
    // 2. check if the junction is connected both ways
    ITrackSegment * frontSegment = m_track->getSelectedForwardEnd();

    if(frontSegment->getSelectedRearEnd() == m_track) {
        m_track = frontSegment;
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
        return ON_TRACK;
    } else {
        qDebug() << "Derailed at junction" << frontSegment->getId();
        qDebug() << "next track's selected rear: " << frontSegment->getSelectedRearEnd()->getId();

        return DERAILED_AT_JUNCTION;
    }
}

train_motion_result TrainLocation::moveToRearTrack(float delta) {
    if(m_track == NULL) {
        m_state = DERAILED_OFF_TRACK;
        return m_state;
    }
    // 1. check if hit terminal
    if(m_track->isRearTerminal()) {
        m_positionOnTrack = 0;
        return HIT_TERMINAL;
    }
    // 2. check if the junction is connected both ways
    ITrackSegment * rearSegment = m_track->getSelectedRearEnd();
    if(rearSegment->getSelectedForwardEnd() == m_track) {
        m_track = rearSegment;
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
        qDebug() << "Derailed at junction" << rearSegment->getId();
        qDebug() << "next track's selected rear: " << rearSegment->getSelectedRearEnd()->getId();
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
    if(m_track == NULL) {
        return QPointF(0,0);
    }
    float R = m_positionOnTrack; // measured from track 'rear-end'
    TrackGeometry* trackPosition = m_track->getTrackGeometry();
    float heading_rads = (180 - trackPosition->getHeading()) * M_PI / 180.0;

    float x = trackPosition->getRearEndPosition().x() + cos(heading_rads) * R;
    float y = trackPosition->getRearEndPosition().y() + sin(heading_rads) * R;

    return QPointF(x,y);
}

int TrainLocation::getTrackId() {
    if(m_track != NULL) {
        return m_track->getId();
    }
    return -1;
}

bool TrainLocation::onTrack() {
    return m_track != NULL;
}

ITrackSegment* TrainLocation::getTrack() {
    return m_track;
}
