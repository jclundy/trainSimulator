#include "systemcontroller.h"

SystemController::SystemController(TrackSystem* system)
{
    m_trackSystem = system;
}

SystemController::~SystemController()
{
    QMapIterator<unsigned int, TrackPathTable*> iterator(m_trainPaths);
    while (iterator.hasNext()) {
        iterator.next();
        int key = iterator.key();
        delete m_trainPaths[key];
        m_trainPaths.remove(key);
    }
}


void SystemController::setAllTrainDestinations(QMap<unsigned int, unsigned int> trainDestinations) {
    QMapIterator<unsigned int, unsigned int> iterator(trainDestinations);
    while (iterator.hasNext()) {
        iterator.next();
        int trainId = iterator.key();
        int destinationTrackId = iterator.value();
        setTrainDestination(trainId, destinationTrackId);
    }
}

void SystemController::setTrainDestination(int trainId, int destinationId) {
    if(m_trainPaths.contains(trainId)) {
        if(m_trainPaths[trainId]->getTargetId() != destinationId) {
            m_trainPaths[trainId]->reset();
            m_trainPaths[trainId]->initialize(m_trackSystem,destinationId);
            m_trainPaths[trainId]->computeTable();
        }
    } else {
        TrackPathTable* table = new TrackPathTable();
        table->initialize(m_trackSystem,destinationId);
        table->computeTable();
        m_trainPaths.insert(trainId, table);
    }
}

void SystemController::controlTrains() {
    QList<Train*> trainList = m_trackSystem->getTrains();
    for(int i = 0; i < trainList.size(); i++) {
        Train* train = trainList.at(i);
        float speed = train->getSpeed();
        TrainLocation location;
        if(speed < 0) {
            location = train->getRearLocation();
        } else {
            location = train->getFrontLocation();
        }
        int trackId = location.getTrackId();

        TrackPathTable* table = m_trainPaths[train->getId()];

        // if we've reached our destination track, stop
        if(table->getTargetId() == trackId) {
            train->stop();
        } else {
            int directionToNext = table->getDirectionToNext(trackId);

            // todo - get this from train class
            float maxSpeed = 5;
            train->setDesiredSpeed(maxSpeed * directionToNext);
        }



        // if track has red signal, stop
        // otherwise, set speed towards next destination
    }
}
