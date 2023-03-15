#include "junction.h"

Junction::Junction(unsigned int maxBranches)
{
    m_maxBranches = maxBranches;
    m_selectedBranch = -1;
}

// getters
QList<ITrackSegment*> Junction::getBranches() {
    return m_branches;
}

int Junction::getSelectedBranchIdx() {
    return m_selectedBranch;
}

ITrackSegment* Junction::getSelectedBranch() {
    if(m_selectedBranch != -1 && m_selectedBranch < m_branches.size()) {
        return m_branches.at(m_selectedBranch);
    }
}

int Junction::getSelectedBranchId() {
    if(m_selectedBranch != -1 && m_selectedBranch < m_branches.size()) {
        return m_branches.at(m_selectedBranch)->getId();
    } else {
        return -1;
    }
}

// setters
bool Junction::addBranch(ITrackSegment* track) {
    if(m_branches.contains(track) == false) {
        m_branches.push_back(track);
        recomputeSelectedBranch();
    }
}

bool Junction::selectBranchByIndex(int idx) {

}

bool Junction::selectBranch(ITrackSegment *track) {

}

bool Junction::selectBranchById(unsigned int id) {

}

void Junction::recomputeSelectedBranch() {
    if(m_selectedBranch < 0 && m_branches.size() > 0) {
        m_selectedBranch = 0;
    } else if (m_selectedBranch >= m_branches.size()) {
        m_selectedBranch = m_branches.size() - 1;
    }
}
