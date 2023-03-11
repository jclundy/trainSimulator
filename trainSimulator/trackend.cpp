#include "trackend.h"
#include <QDebug>

TrackEnd::TrackEnd(TrackSegment *parent, track_pole pole) {
    m_parentTrackSegment = parent;
    m_selectedIndex = 0;
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

Prong* TrackEnd::getSelectedProng() {
    return m_prongList.at(m_selectedIndex);
}

bool TrackEnd::setSelectedProng(int index) {
    if(index >=0 && index < m_prongList.size()) {
        m_selectedIndex = index;
        return true;
    }
    return false;
}

void TrackEnd::toggleSelectedProng() {
    m_selectedIndex++;
    m_selectedIndex %= m_prongList.size();
}

int TrackEnd::findIndexOfProngConnectedToNeighbour(TrackEnd* connector) {
    for(int i = 0; i < m_prongList.size(); i++) {
        if(m_prongList[i]->isNeighbour(connector)) {
            return i;
        }
    }
    return -1;
}

// private methods
void TrackEnd::addProng(float angle, float length) {
    int idx = m_prongList.size();
    Prong* newProng = new Prong(this, idx, angle, length);
    m_prongList.push_back(newProng);
}
