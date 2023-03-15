#include "junction.h"

Junction::Junction(ITrackSegment* parent, unsigned int maxBranches)
{
    m_parent = parent;
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
    return NULL;
}

int Junction::getSelectedBranchId() {
    if(m_selectedBranch != -1 && m_selectedBranch < m_branches.size()) {
        return m_branches.at(m_selectedBranch)->getId();
    } else {
        return -1;
    }
}

int Junction::getNumBranches() {
    return m_branches.size();
}

// setters
bool Junction::addBranch(ITrackSegment* track) {
    if(m_branches.size() < (int) m_maxBranches && m_branches.contains(track) == false) {
        m_branches.push_back(track);
        recomputeSelectedBranch();
        return true;
    }
    return false;
}

bool Junction::selectBranchByIndex(int idx) {
    if(idx < m_branches.size() && idx > 0) {
        m_selectedBranch = idx;
        return true;
    }
    return false;
}

bool Junction::selectBranch(ITrackSegment *track) {
    int idx = m_branches.indexOf(track, 0);
    if(idx > 0 && idx < m_branches.size()) {
        m_selectedBranch = idx;
        return true;
    }
    return false;
}

bool Junction::selectBranchById(unsigned int id) {
    for(int i = 0; i < m_branches.size(); i++) {
        if(m_branches.at(i)->getId() == id) {
            m_selectedBranch = i;
            return true;
        }
    }
    return false;
}

void Junction::removeBranch(ITrackSegment* track) {
    int idx = m_branches.indexOf(track, 0);
    if(idx > 0 && idx < m_branches.size()) {
        track->disconnectFromTrackSegment(m_parent);
        m_branches.removeAt(idx);
    }
}

void Junction::removeAllBranches() {
    for(int i = m_branches.size() - 1; i >= 0; i--) {
        ITrackSegment* neighbour = m_branches.at(i);
        neighbour->disconnectFromTrackSegment(m_parent);
        m_branches.removeLast();
    }
}

void Junction::recomputeSelectedBranch() {
    if(m_selectedBranch < 0 && m_branches.size() > 0) {
        m_selectedBranch = 0;
    } else if (m_selectedBranch >= m_branches.size()) {
        m_selectedBranch = m_branches.size() - 1;
    }
}
