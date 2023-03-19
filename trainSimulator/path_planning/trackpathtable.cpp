#include "trackpathtable.h"
#include <QDebug>

TrackPathTable::TrackPathTable()
{

}

TrackPathTable::~TrackPathTable() {
    reset();
}

void TrackPathTable::reset() {
    QMapIterator<unsigned int, PathTableEntry*> unVisitedIterator(m_unvisited);
    while (unVisitedIterator.hasNext()) {
        unVisitedIterator.next();
        int key = unVisitedIterator.key();
        delete m_unvisited[key];
        m_unvisited.remove(key);
    }

    QMapIterator<unsigned int, PathTableEntry*> tableIterator(m_table);
    while (tableIterator.hasNext()) {
        tableIterator.next();
        int key = tableIterator.key();
        delete m_table[key];
        m_table.remove(key);
    }

    m_table.clear();
    m_unvisited.clear();

}

void TrackPathTable::initialize(TrackSystem *trackSystem, unsigned int targetId) {

    reset();

    m_targetId = targetId;
    m_trackSystem = trackSystem;
    m_maxIterations = trackSystem->getTrackSegments().size();

    for(int i = 0; i < trackSystem->getTrackSegments().size(); i++) {
        ITrackSegment* track = trackSystem->getTrackSegments().at(i);

        PathTableEntry* entry = new PathTableEntry(track->getId(), track->getLength());
        m_table.insert(entry->getTrackId(), entry);
        m_unvisited.insert(entry->getTrackId(), entry);
    }

}

void TrackPathTable::computeTable() {
    // run
    int currentId = m_targetId;
    m_table[currentId]->initializeAsTarget();

    int iterations = 0;

    while(m_unvisited.size() > 0 && iterations < m_maxIterations) {
        iterations++;

        // 1. Set current entry as visited from set of unvisited
        PathTableEntry* currentEntry = m_table[currentId];
        currentEntry->setVisited();

        // 2. Update neighbours of current
        ITrackSegment* currentTrack = m_trackSystem->getTrackSegmentById(currentId);
        float currentDistance = m_table[currentId]->getDistanceToTarget();

        if(currentTrack != NULL) {

            QList<ITrackSegment*> forwardNeighbours = currentTrack->getForwardNeighbours();
            for(int i = 0; i < forwardNeighbours.size(); i++) {

                ITrackSegment* neighbour = forwardNeighbours.at(i);
                PathTableEntry* neighbourEntry = m_table[neighbour->getId()];

                // 'reverse' direction, as we would reverse neighbour to get to current
                neighbourEntry->update(currentId, currentDistance, PATH_REVERSE_DIRECTION);
            }

            QList<ITrackSegment*> rearNeighbours = currentTrack->getRearNeighbours();

            for(int i = 0; i < rearNeighbours.size(); i++) {
                ITrackSegment* neighbour = rearNeighbours.at(i);
                PathTableEntry* neighbourEntry = m_table[neighbour->getId()];

                // 'forward' direction, as we would go forward from neighbour to get to current
                neighbourEntry->update(currentId, currentDistance, PATH_FORWARD_DIRECTION);
            }
        }

        //3. Remove current from list of unvisited
        m_unvisited.remove(currentId);

        //4. Find next closest node and repeat
        currentId = findIdOfClosest();

        if(currentId == -1) {
            return;
        }
    }


}

int TrackPathTable::findIdOfClosest() {

    QMapIterator<unsigned int, PathTableEntry*> i(m_unvisited);
    int closestId = -1;
    float closestDistance = -1;

    if(i.hasNext()) {
        i.next();
        closestId = i.key();
        closestDistance = m_unvisited[closestId]->getDistanceToTarget();
    } else {
        return -1;
    }

    while (i.hasNext()) {
        i.next();
        int newId = i.key();
        PathTableEntry* entry = m_unvisited[newId];

        if(entry == NULL) {
            qDebug() << "TrackPathTable::findIdOfClosests - unvisited node is NULL";
            continue;
        }

        // if entry is already visited, continue
        if(entry->getVisited()) {
            qDebug() << "TrackPathTable::findIdOfClosests - error unvisited node already visited";
            continue;
        }

        float newDistance = entry->getDistanceToTarget();

        if(closestDistance == -1 && newDistance >= 0) {
            closestId = newId;
            closestDistance = newDistance;
        } else {
            if(closestDistance >= 0 && newDistance >= 0) {
                if (newDistance < closestDistance) {
                    closestId = newId;
                    closestDistance = newDistance;
                }
            }
        }
    }

    return closestId;
}


int TrackPathTable::getDirectionToNext(unsigned int trackId) {

    if(m_table.contains(trackId)) {
        return m_table[trackId]->getDirectionToNext();
    }
    return 0;
}
int TrackPathTable::getNextTrackId(unsigned int currentTrackId) {
    if(m_table.contains(currentTrackId)) {
        return m_table[currentTrackId]->getNextId();
    }
    return 0;
}

QList<path_step> TrackPathTable::getPathListFrom(unsigned int trackId) {
    QList<path_step> pathList;

    unsigned int currentId = trackId;

    if(m_table.contains(trackId)) {

        int iterations = 0;
        do {
            path_step step;
            step.trackId = currentId;
            step.nextTrackId = m_table[currentId]->getNextId();
            step.directionToNext = m_table[currentId]->getDirectionToNext();

            currentId = step.nextTrackId;
            pathList.append(step);
            iterations++;
        } while(currentId != m_targetId && iterations < m_maxIterations);

    }

    return pathList;
}

int TrackPathTable::getTargetId() {
    return m_targetId;
}
