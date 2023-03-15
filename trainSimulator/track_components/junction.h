#ifndef JUNCTION_H
#define JUNCTION_H

#include <QList>
#include "itracksegment.h"

class Junction
{
public:
    Junction(unsigned int maxBranches = 2);

    // getters
    QList<ITrackSegment*> getBranches();
    int getSelectedBranchIdx();
    ITrackSegment* getSelectedBranch();
    int getSelectedBranchId();

    // setters
    bool addBranch(ITrackSegment* track);
    bool selectBranchByIndex(int idx);
    bool selectBranch(ITrackSegment *track);
    bool selectBranchById(unsigned int id);

private:
    unsigned int m_maxBranches;
    QList<ITrackSegment*> m_branches;
    int m_selectedBranch;
};

#endif // JUNCTION_H
