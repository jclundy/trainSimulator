#ifndef TRACKPATHTABLE_H
#define TRACKPATHTABLE_H

#include "track_system/tracksystem.h"
#include <QList>
#include <QMap>

typedef struct {
    unsigned int trackId;
    int trackLength;
    int distanceToTarget;
    unsigned int nextId;
    int directionToNext; //-1=reverse, 1=forward, 0=stop
} path_table_entry;

typedef struct {
    unsigned int trackId;
    int directionToNext; //-1=reverse, 1=forward, 0=stop
} path_step;

class TrackPathTable
{
public:
    TrackPathTable();
    void initialize(TrackSystem *trackSystem, unsigned int targetId);
    void computeTable();
    int getDirectionToNext(unsigned int trackId);
    QList<path_step> getPathListFrom(unsigned int trackId);

private:
    TrackSystem* m_trackSystem;
    QMap<unsigned int, path_table_entry> m_table;
    unsigned int m_targetId;
};

#endif // TRACKPATHTABLE_H
