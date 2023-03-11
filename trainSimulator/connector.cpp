#include "connector.h"

Connector::Connector(TrackSegment *parentTrackSegment, track_end trackEnd) {
    m_parentTrackSegment = parentTrackSegment;
    m_connectionType = TERMINAL;
    m_position.setX(0);
    m_position.setY(0);
    m_trackEnd = trackEnd;
}

// public methods
connector_type Connector::getConnectionType() {
    return m_connectionType;
}

bool Connector::isFront() {
    return m_trackEnd == TRACK_FRONT;
}

bool Connector::isRear() {
    return m_trackEnd = TRACK_REAR;
}

bool Connector::isTerminal() {
    return m_connectionType == TERMINAL;
}

bool Connector::isFork() {
    return m_connectionType == FORK;
}

// modifiers
bool Connector::connectTo(Connector* neighbour) {
    // check if neighbour can be connected to

    if(m_fork == NULL) {

    }
}

// search methods
TrackSegment* Connector::getTrackSegment();
TrackSegment* Connector::getConnectedTrackSegment();
Connector* Connector::getNeighbouringConnection();
