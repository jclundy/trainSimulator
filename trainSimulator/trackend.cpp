#include "trackend.h"
#include <QDebug>

TrackEnd::TrackEnd(TrackSegment *parent) {
    m_parentConnector = parent;
    m_selectedIndex = 0;
    // always have one 'prong' by default
    addProng();
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
