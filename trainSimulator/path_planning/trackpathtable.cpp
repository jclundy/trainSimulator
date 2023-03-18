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
        m_unvisited.insert(track->getId(), track);

        PathTableEntry entry = PathTableEntry(track->getId(), track->getLength());
        m_table.insert(entry.getTrackId(), entry);
    }

}

void TrackPathTable::computeTable() {
    // run
    int currentId = m_targetId;

    while(m_unvisited.size() > 0) {
        // 1. Set current entry as visited from set of unvisited
        PathTableEntry currentEntry = m_table[m_targetId];
        currentEntry.setVisited();

        // 2. Update neighbours of current
        ITrackSegment* currentTrack = m_unvisited[currentId];
        float currentDistance = m_table[currentId].getDistanceToTarget();

        if(currentTrack != NULL) {
            QList<ITrackSegment*> forwardNeighbours = currentTrack->getForwardNeighbours();
            for(int i = 0; i < forwardNeighbours.size(); i++) {
                ITrackSegment* neighbour = forwardNeighbours.at(i);
                PathTableEntry neighbourEntry = m_table[neighbour->getId()];
                // 'reverse' direction, as we would reverse neighbour to get to current
                neighbourEntry.update(currentId, currentDistance, PATH_REVERSE_DIRECTION);
            }

            QList<ITrackSegment*> rearNeighbours = currentTrack->getRearNeighbours();
            for(int i = 0; i < rearNeighbours.size(); i++) {
                ITrackSegment* neighbour = rearNeighbours.at(i);
                PathTableEntry neighbourEntry = m_table[neighbour->getId()];
                // 'forward' direction, as we would go forward from neighbour to get to current
                neighbourEntry.update(currentId, currentDistance, PATH_FORWARD_DIRECTION);
            }
        }

        //3. Remove current from list of unvisited
        m_unvisited.remove(currentEntry.getTrackId());

        //4. Find next closest node and re[eat
        currentId = findIdOfClosest();
        if(currentId == -1) {
            return;
        }
    }


}

int TrackPathTable::findIdOfClosest() {

    int closestId = -1;
    float closestDistance = -1;

    QMapIterator<unsigned int, PathTableEntry> i(m_table);
    while (i.hasNext()) {
        i.next();
        float newId = i.key();
        PathTableEntry entry = m_table[newId];
        float newDistance = entry.getDistanceToTarget();


        if(closestId == -1) {
            closestId = newId;
            closestDistance = newDistance;
        } else {
            if(closestDistance == -1 && newDistance >= 0) {
                closestId = newId;
                closestDistance = newDistance;
            } else if (newDistance < closestDistance) {
                closestId = newId;
                closestDistance = newDistance;
            }
        }
    }

    return closestId;
}


int TrackPathTable::getDirectionToNext(unsigned int trackId) {
    return 0;
}

QList<path_step> TrackPathTable::getPathListFrom(unsigned int trackId) {
    QList<path_step> pathList;
    return pathList;
}
