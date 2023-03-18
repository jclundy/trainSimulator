#include "trackpathtable.h"

TrackPathTable::TrackPathTable()
{

}

void TrackPathTable::initialize(TrackSystem *trackSystem, unsigned int targetId) {
    m_table.clear();
    m_targetId = targetId;
    m_trackSystem = trackSystem;

    for(int i = 0; i < trackSystem->getTrackSegments().size(); i++) {
        ITrackSegment* track = trackSystem->getTrackSegments().at(i);
        path_table_entry entry;
        entry.trackId = track->getId();
        entry.trackLength = track->getLength();
        entry.directionToNext = 0;
        entry.distanceToTarget = -1;
        entry.nextId = track->getId();
        entry.visited = false;
        m_table.insert(entry.trackId, entry);
        m_unvisited.insert(entry.trackId, track);
    }

}

void TrackPathTable::computeTable() {
    // run
    path_table_entry rootEntry = m_table[m_targetId];
    rootEntry.distanceToTarget = 0;
    rootEntry.directionToNext = 0;
    rootEntry.nextId = m_targetId;
    rootEntry.visited = true;
    m_table[m_targetId] = rootEntry;

    int currentId = m_targetId;
    ITrackSegment* currentTrack = m_unvisited[currentId];
    if(currentTrack != NULL) {
        QList<ITrackSegment*> forwardNeighbours = currentTrack->getForwardNeighbours();
        for(int i = 0; i < forwardNeighbours.size(); i++) {
            ITrackSegment* neighbour = forwardNeighbours.at(i);
            auto neighbour_id = neighbour->getId();

            float newDistanceToTarget = m_table[currentId].distanceToTarget + neighbour->getLength();
            if(m_table[neighbour_id].distanceToTarget == -1) {
                m_table[neighbour_id].distanceToTarget = newDistanceToTarget;
//                m_tab
            }
        }

    }
    m_table.remove(currentId);

}

int TrackPathTable::getDirectionToNext(unsigned int trackId) {
    return 0;
}

QList<path_step> TrackPathTable::getPathListFrom(unsigned int trackId) {
    QList<path_step> pathList;
    return pathList;
}
