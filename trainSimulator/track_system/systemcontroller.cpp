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

        float newDesiredSpeed = train->getSpeed();
        //1. Control speed based on destination
        if(table->getTargetId() == trackId) {
            // if we've reached our destination track, stop
            train->stop();
            newDesiredSpeed = 0;
        } else {
            int directionToNext = table->getDirectionToNext(trackId);

            float maxSpeed = train->getMaxSpeed();
            newDesiredSpeed = maxSpeed * directionToNext;
        }
        //2. Check signals
        // if track has red signal, stop
        // otherwise, set speed towards next destination
        ITrackSegment* trackSegment;
        ISignal* signal;
        if(newDesiredSpeed < 0) {
            trackSegment = train->getRearLocation().getTrack();
            signal = trackSegment->getRearSignal();
        } else {
            trackSegment = train->getFrontLocation().getTrack();
            signal = trackSegment->getFrontSignal();
        }
        if(signal != NULL) {
            if(signal->isRed()) {
                newDesiredSpeed = 0;
            }
        }
        train->setDesiredSpeed(0);
    }
}
