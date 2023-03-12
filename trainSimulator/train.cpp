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
    QPointF midpoint = track->getCenter();

    if(orientation == TRAIN_HEAD_TOWARDS_TRACK_FRONT) {
        QPointF headPosition = midpoint + m_length/2;

        // initialize front location to

    }
}
