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

void PathTableEntry::initializeAsTarget() {
    m_nextId = m_trackId;
    m_directionToNext = 0;
    m_visited = true;
    m_distanceToTarget = 0;
}

void PathTableEntry::update(unsigned int neighbourId, float neighbourDistance, path_direction direction) {
    // if uninitialized or neighbour is closer to the target, update our closest neighbour

    if(m_distanceToTarget == -1) {
        m_nextId = neighbourId;
        m_distanceToTarget = neighbourDistance + m_trackLength;
        m_directionToNext = direction;

    } else {
         if(neighbourDistance + m_trackLength < m_distanceToTarget) {
             m_nextId = neighbourId;
             m_distanceToTarget = neighbourDistance + m_trackLength;
             m_directionToNext = direction;
         }
    }
}

bool PathTableEntry::getVisited() {
    return m_visited;
}

void PathTableEntry::setVisited() {
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
