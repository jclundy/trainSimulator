#ifndef TRACKPATHTABLE_H
#define TRACKPATHTABLE_H

#include "track_system/tracksystem.h"
#include "pathtableentry.h"

#include <QList>
#include <QMap>

typedef struct {
    unsigned int trackId;
    int directionToNext; //-1=reverse, 1=forward, 0=stop
    unsigned int nextTrackId;
} path_step;

class TrackPathTable
{
public:
    TrackPathTable();
    ~TrackPathTable();
    void reset();
    void initialize(TrackSystem *trackSystem, unsigned int targetId);
    void computeTable();
    int getDirectionToNext(unsigned int trackId);
    QList<path_step> getPathListFrom(unsigned int trackId);
    int getTargetId();

private:
    int findIdOfClosest();

    TrackSystem* m_trackSystem;
    QMap<unsigned int, PathTableEntry*> m_table;
    QMap<unsigned int, PathTableEntry*> m_unvisited;
    unsigned int m_targetId;
    int m_maxIterations;
};

#endif // TRACKPATHTABLE_H
