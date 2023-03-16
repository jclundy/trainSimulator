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

bool TrackSystem::areAllTrainsStopped() {
    bool stopped = true;
    for(int i = 0; i < m_trains.size(); i++) {
        stopped &= m_trains.at(i)->isStopped();
    }
    return stopped;
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

Train* TrackSystem::getTrainById(unsigned int id) {
    for(int i = 0; i < m_trains.size(); i++) {
        if(m_trains.at(i)->getId() == id) {
            return m_trains.at(i);
        }
    }
    return NULL;
}

JunctionTrack* TrackSystem::getJunctionById(unsigned int id) {
    for(int i = 0; i < m_junctions.size(); i++) {
        if(m_junctions.at(i)->getId() == id) {
            return m_junctions.at(i);
        }
    }
    return NULL;
}

ITrackSegment* TrackSystem::getTrackSegmentById(unsigned int id) {
    for(int i = 0; i < m_trackSegments.size(); i++) {
        if(m_trackSegments.at(i)->getId() == id) {
            return m_trackSegments.at(i);
        }
    }
    return NULL;
}

/* Adders */
Train* TrackSystem::addTrain() {
    Train* train = new Train(m_nextAvailableTrainId);
    m_nextAvailableTrainId++;

    m_trains.push_back(train);

    return train;
}

LinearTrack* TrackSystem::addLinearTrack() {
    LinearTrack* track = new LinearTrack(m_nextAvailableTrackId);
    m_nextAvailableTrackId++;
    m_trackSegments.push_back(track);
    return track;
}

JunctionTrack* TrackSystem::addJunctionTrack() {
    JunctionTrack* track = new JunctionTrack(m_nextAvailableTrackId);
    m_nextAvailableTrackId++;
    m_trackSegments.push_back(track);
    m_junctions.push_back(track);
    return track;
}
