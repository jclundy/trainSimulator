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

    /* Idea 1:
     * The algorithm for this should be very simple
     * If a train is approaching a junction,
     * get the train's target track and switch to that branch
     *
     * If 2 trains are approaching a junction,
     * select the branch for the train that has higher priority
     *
     * Requirements
     * TrackPath from Train
     */

    /* Idea 2:
     * Have a separate TrainPathController class
     * this will have knowledge of the train's paths
     * and will update the junctions
     *
     * maybe:
     * TrackSystem implements 'driveIndividualJunction' method
     * setJunctionRearBranch(id)
     * setJunctionFrontBranch(id)
     */
}

void TrackSystem::driveSignals() {
    // Todo - implement me

    /* Should follow the following simple rules:
     *
     * For signals on track ends:
     * Always signal RED if on a terminal
     *
     * For signal on end of track:
     * if there is a train going forward, and in forward track there is a train
     * moving slower, stopped or reverse, signal RED
     *
     * if three is a train going reverse, and in previous track there is a a train
     * moving slower, stopped or forward, signal RED
     *
     * For signals on junctions:
     * Follow rules above
     * If junction branch is disconnected, signal RED
     *
     *
     * otherwise signal GREEN
     */

    /* Signals are only one-directional
     * Signal on rear of a segment faces trains reversing though the segment
     * Signal on the front of a segment faces trains going forward through the segment
     */
}

void TrackSystem::driveTrains(float dt) {
    /* The algorithm for this should be very simple
     * A separate class, ie TrainPathController or TrainDriver
     * will set the speed setpoints for the train
     * This method will simply iterate through the list of trains
     * and increment their position
     */
    for(int i = 0; i < m_trains.size(); i++) {
        m_trains.at(i)->drive(dt);
    }
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
