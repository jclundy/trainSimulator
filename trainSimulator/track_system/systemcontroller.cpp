#include "systemcontroller.h"
#include <math.h>

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

        float currentSpeed = train->getSpeed();
        float newDesiredSpeed = currentSpeed;
        int directionToNext = table->getDirectionToNext(trackId);

        //1. Control speed based on destination
        if(table->getTargetId() == trackId) {
            // slow down to 1 m/s
            newDesiredSpeed = copysign(1.0, currentSpeed);
            // if we've reached our destination track, stop when reaching midpoint
            if(currentSpeed < 0) {
                // stop when our rear is at midpoint of track
                if(location.getPositionOnTrack() > location.getTrack()->getLength()/2) {
                    newDesiredSpeed = 0;
                }
            } else {
                // stop when our rear is at midpoint of track
                if(location.getPositionOnTrack() > location.getTrack()->getLength()/2) {
                    newDesiredSpeed = 0;
                }
            }
        } else {

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
                newDesiredSpeed = copysign(1.0, currentSpeed);
                if(newDesiredSpeed > 0 && location.getPositionOnTrack() > location.getTrack()->getLength() - train->getLength() * 1.5) {
                    newDesiredSpeed = 0;
                } else if (newDesiredSpeed < 0 && location.getPositionOnTrack() < train->getLength() * 1.5) {
                    newDesiredSpeed = 0;
                }
            }
        }
        train->setDesiredSpeed(newDesiredSpeed);
    }
}

void SystemController::stopAllTrains() {
    QList<Train*> trainList = m_trackSystem->getTrains();
    for(int i = 0; i < trainList.size(); i++) {
        Train* train = trainList.at(i);
        train->stop();
    }
}

QMap<unsigned int, TrackPathTable*> SystemController::getTrainPaths() {
    return m_trainPaths;
}
