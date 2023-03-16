#include "signal.h"

Signal::Signal()
{
    m_state = true;
    m_trackSegment = NULL;
    m_position = SIGNAL_UNPLACED;
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

signal_position Signal::getPosition() {
    return m_position;
}
