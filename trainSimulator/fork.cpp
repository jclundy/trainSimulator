#include "connector.h"
#include <QDebug>

Fork::Fork(Connector *parent) {
    m_parentConnector = parent;
    m_selectedIndex = 0;
    // always have one 'prong' by default
    addProng();
}

Prong* Fork::getSelectedProng() {
    return m_prongList.at(m_selectedIndex);
}

bool Fork::setSelectedProng(unsigned int index) {
    if(index >=0 && index < m_prongList.size()) {
        m_selectedIndex = index;
        return true;
    }
    return false;
}

void Fork::toggleSelectedProng() {
    m_selectedIndex++;
    m_selectedIndex %= m_prongList.size();
}

int Fork::findIndexOfProngConnectedToNeighbour(Connector* connector) {
    for(int i = 0; i < m_prongList.size(); i++) {
        if(m_prongList[i]->isNeighbour(connector)) {
            return i;
        }
    }
    return -1;
}

// private methods
void Fork::addProng(float angle, float length) {
    int idx = m_prongList.size();
    Prong* newProng = new Prong(this, idx, angle, length);
    m_prongList.push_back(newProng);
}
