#include "train.h"

#include <QDebug>

Train::Train(float length)
{
    direction = 1;
    // initialize front location
    // initialize rear location
    m_speed = 0;
    m_acceleration = 0;
    m_length = length;
    m_isDriving = false;
}

void Train::place(TrackSegment *track, train_orientation orientation) {
    if(m_isDriving) {
        qDebug() << "can't re-position train while driving";
        return;
    }

    float midpoint = track->getLength()/2;
    float headPosition = 0;
    float rearPosition = 0;

    if(orientation == TRAIN_HEAD_TOWARDS_TRACK_FRONT) {
        headPosition = midpoint + m_length/2;
        rearPosition = midpoint - m_length/2;
    } else {
        headPosition = midpoint - m_length/2;
        rearPosition = midpoint + m_length/2;
    }

    frontLocation.resetPosition(track, headPosition);
    rearLocation.resetPosition(track, rearPosition);
}

void Train::setStartingSpeed(float speed) {
    if(m_isDriving) {
        qDebug() << "can't reset train speed while driving";
        return;
    }
    m_speed = speed;
}

void Train::drive(float dt) {
    m_isDriving = true;
}

void Train::stop() {
    m_isDriving = false;
}
