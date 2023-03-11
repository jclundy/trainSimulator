#include "connector.h"

Prong::Prong(Fork* parent, uint8_t idx, float angle, float length) {
    m_parentFork = parent;
    m_angle = angle;
    m_length = length;
    m_index = idx;
}

bool Prong::isNeighbourConnected() {
    return false;
}

void Prong::connect(Prong *neighbour) {
    m_neighbour = neighbour;
}

bool Prong::isNeighbour(Connector* connector) {
    if(m_neighbour == NULL) {
        return false;
    } else {
        return m_neighbour->m_parentFork->m_parentConnector == connector;
    }
}
