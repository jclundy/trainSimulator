#include "pathtableentry.h"

PathTableEntry::PathTableEntry(unsigned int id, float trackLength)
{
    m_trackId = id;
    m_trackLength = trackLength;
    m_distanceToTarget = -1;

    m_nextId = id;
    m_directionToNext = 0;

    m_visited = false;

}


void PathTableEntry::update(unsigned int neighbourId, float neighbourDistance) {

}

bool PathTableEntry::getVisited() {
    return m_visited;
}

bool PathTableEntry::setVisited() {
    m_visited = true;
}

unsigned int PathTableEntry::getTrackId() {
    return m_trackId;
}

float PathTableEntry::getTrackLength() {
    return m_trackLength;
}

float PathTableEntry::getDistanceToTarget() {
    return m_distanceToTarget;
}

float PathTableEntry::getNextId() {
    return m_nextId;
}

int PathTableEntry::getDirectionToNext() {
    return m_directionToNext;
}
