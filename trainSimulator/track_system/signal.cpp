#include "signal.h"

Signal::Signal()
{
    m_state = true;
    m_trackSegment = NULL;
    m_placement = SIGNAL_UNPLACED;
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

void Signal::placeOnTrackFront(ITrackSegment* track) {
    if(m_trackSegment->placeFrontSignal(this)) {
        m_placement = SIGNAL_TRACK_FRONT;
        m_trackSegment = track;
    }
}

void Signal::placeOnTrackRear(ITrackSegment* track) {
    if(m_trackSegment->placeRearSignal(this)) {
        m_placement = SIGNAL_TRACK_REAR;
        m_trackSegment = track;
    }
}
