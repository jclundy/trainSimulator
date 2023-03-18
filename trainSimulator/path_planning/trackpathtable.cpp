#include "trackpathtable.h"

TrackPathTable::TrackPathTable()
{

}

void TrackPathTable::initialize(QList<ITrackSegment*> trackList, unsigned int targetId) {
    m_table.clear();
    m_targetId = targetId;

    for(int i = 0; i < trackList.size(); i++) {
        ITrackSegment* track = trackList.at(i);
        path_table_entry entry;
        entry.trackId = track->getId();
        entry.trackLength = track->getLength();
        entry.directionToNext = 0;
        entry.distanceToTarget = -1;
        entry.nextId = track->getId();
        m_table.insert(entry.trackId, entry);
    }
}

void TrackPathTable::computeTable() {

}

int TrackPathTable::getDirectionToNext(unsigned int trackId) {
    return 0;
}

QList<path_step> TrackPathTable::getPathListFrom(unsigned int trackId) {
    QList<path_step> pathList;
    return pathList;
}
