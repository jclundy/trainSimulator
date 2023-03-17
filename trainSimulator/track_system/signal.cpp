#include "signal.h"

Signal::Signal(unsigned int id)
{
    m_state = true;
    m_trackSegment = NULL;
    m_placement = SIGNAL_UNPLACED;
    m_id = id;
}

Signal::~Signal()
{

}

bool Signal::isRed() {
    return m_state == false;
}

bool Signal::isGreen() {
    return m_state;
}

void Signal::update() {
    // Todo - implement me

    /* Should follow the following simple rules:
     *
     * For signals on track ends:
     * Always signal RED if on a terminal
     *
     * For signal on end of track:
     * if there is a train going forward, and in forward track there is a train
     * moving slower, stopped or reverse, signal RED
     *
     * if three is a train going reverse, and in previous track there is a a train
     * moving slower, stopped or forward, signal RED
     *
     * For signals on junctions:
     * Follow rules above
     * If junction branch is disconnected, signal RED
     *
     *
     * otherwise signal GREEN
     */

    /* Signals are only one-directional
     * Signal on rear of a segment faces trains reversing though the segment
     * Signal on the front of a segment faces trains going forward through the segment
     */
}

unsigned int Signal::getId() {
    return m_id;
}

void Signal::setRed() {
    setState(false);
}

void Signal::setGreen() {
    setState(true);
}

void Signal::setState(bool state) {
    m_state = state;
}

ITrackSegment* Signal::getTrackSegment() {
    return m_trackSegment;
}

signal_placement Signal::getPlacement() {
    return m_placement;
}

bool Signal::placeOnTrackFront(ITrackSegment* track) {
    if(m_trackSegment != NULL) {
        return false;
    }
    if(track->placeFrontSignal(this)) {
        m_placement = SIGNAL_TRACK_FRONT;
        m_trackSegment = track;
        return true;
    }
    return false;
}

bool Signal::placeOnTrackRear(ITrackSegment* track) {
    if(m_trackSegment != NULL) {
        return false;
    }
    if(track->placeRearSignal(this)) {
        m_placement = SIGNAL_TRACK_REAR;
        m_trackSegment = track;
        return true;
    }
    return false;
}
