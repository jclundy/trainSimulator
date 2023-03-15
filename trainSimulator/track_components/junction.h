#ifndef JUNCTION_H
#define JUNCTION_H

#include <QList>
#include "itracksegment.h"

class Junction
{
public:
    Junction(ITrackSegment* parent, unsigned int maxBranches);

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
    void removeBranch(ITrackSegment* track);
    void removeAllBranches();


private:
    unsigned int m_maxBranches;
    QList<ITrackSegment*> m_branches;
    int m_selectedBranch;
    ITrackSegment* m_parent;

    // private methods
    void recomputeSelectedBranch();
};

#endif // JUNCTION_H
