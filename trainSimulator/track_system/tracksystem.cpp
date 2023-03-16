#include "tracksystem.h"

TrackSystem::TrackSystem(unsigned int maxForksPerJunction, int defaultTrackLength)
{
    m_maxForksPerJunction = maxForksPerJunction;
    m_defaultTrackLength = defaultTrackLength;
    m_nextAvailableTrackId = 0;
    m_nextAvailableTrainId = 0;
    m_nextAvailableSignalId = 0;

}

/* Drivers */
void TrackSystem::driveJunctions() {
    // Todo - implement me
}

void TrackSystem::driveSignals() {
    // Todo - implement me
}

void TrackSystem::driveTrains(float dt) {
    // Todo - implement m
}

/* Getters */
QList<Train*> TrackSystem::getTrains() {
    return m_trains;
}

QList<JunctionTrack*> TrackSystem::getJunctions() {
    return m_junctions;
}

QList<ITrackSegment*> TrackSystem::getTrackSegments() {
    return m_trackSegments;
}

Train* TrackSystem::getTrainById() {
    return NULL;
}

JunctionTrack* TrackSystem::getJunctionById() {
    return NULL;
}

ITrackSegment* TrackSystem::getTrackSegmentById() {
    return NULL;
}

/* Adders */
Train* TrackSystem::addTrain() {
    return NULL;
}

LinearTrack* TrackSystem::addLinearTrack() {
    return NULL;
}

JunctionTrack* TrackSystem::addJunctionTrack() {
    return NULL;
}
