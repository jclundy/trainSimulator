#include "trackend.h"
#include <QDebug>

TrackEnd::TrackEnd(TrackSegment *parent, track_pole pole) {
    m_parentTrackSegment = parent;
    m_selectedIndex = -1;
    m_pole = pole;

    // position
    m_position.setX(0);
    m_position.setY(0);
}

bool TrackEnd::isFront() {
    return m_pole == TRACK_FRONT;
}

bool TrackEnd::isRear() {
    return m_pole == TRACK_REAR;
}

bool TrackEnd::isTerminal() {
    return m_neighbourList.size() == 0;
}

bool TrackEnd::isFork() {
    return m_neighbourList.size() >= 2;
}

bool TrackEnd::connectTo(TrackEnd *neighbour) {
    if(m_neighbourList.size() >= TrackEnd::maxForks()) {
        return false;
    }
    if(neighbour->m_neighbourList.size() > TrackEnd::maxForks()) {
        return false;
    }
    if(neighbour->isFront() && isFront()) {
        return false;
    }
    if(neighbour->isRear() && isRear()) {
        return false;
    }

    m_neighbourList.push_back(neighbour);
    neighbour->m_neighbourList.push_back(this);

    return true;
}

void TrackEnd::disconnect(TrackEnd* neighbour) {
    // remove me from neighbour's list
    int neighbourIdxForMe = getNeighboursForkNumberForMe(neighbour);
    if(neighbourIdxForMe != -1) {
        neighbour->m_neighbourList.removeAt(neighbourIdxForMe);
        neighbour->validateSelectedForkNumber();
    }
    // remove neighbour from my list
    int myIdxForNeighbour = getMyForkNumberForNeighbour(neighbour);
    if(myIdxForNeighbour != -1) {
        m_neighbourList.removeAt(myIdxForNeighbour);
        validateSelectedForkNumber();
    }
}

void TrackEnd::disconnectAll() {
    for (int i = m_neighbourList.size() - 1; i >= 0; i--) {
        disconnect(m_neighbourList[i]);
    }
}

void TrackEnd::validateSelectedForkNumber() {
    if(m_selectedIndex > m_neighbourList.size()) {
        m_selectedIndex = m_neighbourList.size() - 1;
    }
}

TrackSegment* TrackEnd::getSelectedTrackSegment() {
    if(m_selectedIndex >= 0) {
        return m_neighbourList.at(m_selectedIndex)->m_parentTrackSegment;
    }
    return NULL;
}

TrackEnd* TrackEnd::getSelectedTrackEnd() {
    if(m_selectedIndex >= 0) {
        return m_neighbourList.at(m_selectedIndex);
    }
    return NULL;
}

int TrackEnd::getSelectedForkNumber() {
    return m_selectedIndex;
}


bool TrackEnd::isNeighbour(TrackEnd* connector, int &forkNumber) {
    forkNumber = m_neighbourList.indexOf(connector);
    return forkNumber != -1;
}
int TrackEnd::getMyForkNumberForNeighbour(TrackEnd* neighbour) {
    int number = -1;
    if(isNeighbour(neighbour, number)) {
        return number;
    }
    return number;
}

int TrackEnd::getNeighboursForkNumberForMe(TrackEnd* neighbour) {
    int number = -1;
    if(neighbour->isNeighbour(this, number)) {
        return number;
    }
    return number;
}

bool TrackEnd::isConnectedToNeighbourBothWays() {
    TrackEnd* neighbour = getSelectedTrackEnd();
    return neighbour->getSelectedTrackEnd() == this;
}

bool TrackEnd::setSelectedFork(int index) {
    if(index >=0 && index < m_neighbourList.size()) {
        m_selectedIndex = index;
        return true;
    }
    return false;
}

void TrackEnd::toggleSelectedFork() {
    m_selectedIndex++;
    m_selectedIndex %= m_neighbourList.size();
}
