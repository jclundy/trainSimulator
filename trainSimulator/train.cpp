#include "train.h"

Train::Train(float length)
{
    direction = 1;
    // initialize front location
    // initialize rear location
    m_speed = 0;
    m_acceleration = 0;
    m_length = length;
}

void Train::place(TrackSegment *track, train_orientation orientation) {

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
