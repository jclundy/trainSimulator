#include "simulationlogger.h"
#include <QDebug>

SimulationLogger::SimulationLogger(QString fileName)
{
    m_fileName = fileName;
    m_file = new QFile(fileName);
}

void SimulationLogger::openFile() {
    if (m_file->open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << " opened file";
        m_out.setDevice(m_file);
    }
}

void SimulationLogger::closeFile() {
    m_file->close();
}

void SimulationLogger::setTrackSystem(TrackSystem* trackSystem) {
    m_trackSystem = trackSystem;
}

void SimulationLogger::setTrainPaths(QMap<unsigned int, TrackPathTable*> trainPaths) {
    m_trainPaths = trainPaths;
}

// high-level logging
void SimulationLogger::logTrackSystemInfo() {
    m_out << "=========================== \n";
    m_out << "TRACK SYSTEM INFO  \n";
    m_out << "+++++++++++++++++++++++++++ \n";
    m_out << "List of Trains: \n";
    logAllTrains();
    m_out << "+++++++++++++++++++++++++++ \n";
    m_out << "List of Tracks: \n";
    logAllTracks();
    m_out << "+++++++++++++++++++++++++++ \n";
    m_out << "List of Junctions: \n";
    logAllJunctions();
    m_out << "+++++++++++++++++++++++++++ \n";
    m_out << "List of Signals: \n";
    logAllSignals();
}

void SimulationLogger::logAllTracks() {
    QList<ITrackSegment*> trackList = m_trackSystem->getTrackSegments();
    for(int i = 0; i < trackList.size(); i++) {
        logTrackInfo(trackList.at(i));
    }
}

void SimulationLogger::logAllSignals() {
    QList<Signal*> signalList = m_trackSystem->getSignals();
    for(int i =0; i < signalList.size(); i++) {
        logSignalInfo(signalList.at(i));
    }
}

void SimulationLogger::logAllJunctions() {
    m_out << "-------------------------------------\n";
    m_out << "JUNCTION INFO  \n";
    QList<JunctionTrack*> junctionList = m_trackSystem->getJunctions();
    for(int i = 0; i < junctionList.size(); i++) {
        logJunctionInfo(junctionList.at(i));
    }
}

void SimulationLogger::logAllTrains() {
    QList<Train*> trainList = m_trackSystem->getTrains();
    for(int i = 0; i < trainList.size(); i++) {
        logTrainInfo(trainList.at(0));
    }
}

void SimulationLogger::logTrainPaths() {
    m_out << "=========================== \n";
    m_out << "TRAIN PATH INFO  \n";
    QList<Train*> trainList = m_trackSystem->getTrains();
    for(int i = 0; i < trainList.size(); i++) {
        Train* train = trainList.at(i);
        int trainId = train->getId();
        int trainTrackId = train->getFrontLocation().getTrackId();
        m_out << "-------------------------------------\n";
        m_out << "Path for Train " << trainId << "\n";
        QList<path_step> pathList = m_trainPaths[trainId]->getPathListFrom(trainTrackId);
        m_out << "From track " << trainTrackId <<  " to track " <<  m_trainPaths[trainId]->getTargetId() << "\n";
        logTrackPath(pathList);

    }
}



void SimulationLogger::logTimeStep(int iterations, float elapsedSeconds) {
    m_out << "****************************** \n";
    m_out << "Iteration: " << iterations << ", Time: " << elapsedSeconds << " s \n";
    m_out << "++++++++++++++++++++++++++++++ \n";
    m_out << "Train movements \n";
    logTrainMovements();
//    logAllSignals();
    m_out << "++++++++++++++++++++++++++++++ \n";
    m_out << "Junction states \n";
    logAllJunctions();

    // todo - change to log signal changes and junction changes
}

// logging changed track elements
void SimulationLogger::logTrainMovements() {
    m_out << "Train Movements: \n";
    // logTrainMovements
    QList<Train*> trainList = m_trackSystem->getTrains();
    for(int i = 0; i < trainList.size(); i++) {
        logTrainMovementInfo(trainList.at(i));
    }
}

void SimulationLogger::logChangedSignals() {

}

void SimulationLogger::logChangedJunctions() {

}

// logging for individual components
void SimulationLogger::logTrackInfo(ITrackSegment *track) {
    m_out << "----------------------------\n";
    m_out << "ID " << track->getId() << "\n";
    m_out << "length " << track->getTrackGeometry()->getLength() << "\n";
    m_out << "heading " << track->getTrackGeometry()->getHeading() << "\n";
    m_out << "is junction? " << track->isJunction() << "\n";
    m_out << "Rear Position: ";
    logPoint(track->getTrackGeometry()->getRearEndPosition());
    m_out << "\n";

    m_out << "Front Position:";
    logPoint(track->getTrackGeometry()->getFrontEndPosition());
    m_out << "\n";


    m_out << "Front neighbours: ";
    logNeighbours(track->getForwardNeighbours());

    m_out << "Front neighbours: ";
    logNeighbours(track->getRearNeighbours());

}

void SimulationLogger::logPoint(QPointF point) {
    m_out << "(" << point.x() << "," << point.y() << ")";
}


void SimulationLogger::logNeighbours(QList<ITrackSegment*> list) {
    for(int i = 0; i < list.size(); i++) {
        m_out << list.at(i)->getId();
        if(i < list.size() -1) {
            m_out << ",";
        }
    }
    m_out << "\n";
}

void SimulationLogger::logSignalInfo(Signal* signal) {
    QString color = (signal->isRed())? "RED" : "GREEN";

    ITrackSegment *track = signal->getTrackSegment();
    if(track != NULL) {
        QString placementStr = "";
        auto placement = signal->getPlacement();
        if(placement == SIGNAL_TRACK_FRONT) {
            placementStr = " Front";
        } else if (placement == SIGNAL_TRACK_REAR) {
            placementStr = " Rear";
        }

        m_out << "Signal ID " << signal->getId() << "; on Track " << track->getId() << placementStr << "; state=" << color  << "\n";
    } else {
        m_out << "Signal ID " << signal->getId() << "; not placed " << "; state=" << color  << "\n";
    }
}

void SimulationLogger::logJunctionInfo(JunctionTrack* track) {
    m_out << "Junction ID " << track->getId() << "\n";
    m_out << "Selected front " << track->getSelectedForwardEnd()->getId() << "\n";
    m_out << "Selected rear " << track->getSelectedRearEnd()->getId() << "\n";
}

void SimulationLogger::logTrainInfo(Train* train) {
    m_out << "Train ID: " << train->getId() << "\n";
    m_out << "Train length " << train->getLength()  << "\n";
    m_out << "Train max speed " << train->getMaxSpeed()  << "\n";
    m_out << "Train track id: " << train->getFrontLocation().getTrackId() << ", " << train->getFrontLocation().getPositionOnTrack() << " meters from track rear"  << "\n";
}

void SimulationLogger::logTrainMovementInfo(Train* train) {
    m_out << "-------------------------------------\n";
    m_out << "Train ID: " << train->getId() << "\n";
    m_out << "Train speed: " << train->getSpeed() << "\n";
    m_out << "Train front world location";
    logPoint(train->getFrontLocationInWorld());
    m_out << "\n";
    m_out << "Train track id: " << train->getFrontLocation().getTrackId() << ", " << train->getFrontLocation().getPositionOnTrack() << " meters from track rear"  << "\n";
}

void SimulationLogger::logTrackPath(QList<path_step> pathList) {
    m_out << "Track Path:" << "\n";
    for (int i = 0; i < pathList.size(); i++) {
        path_step step = pathList.at(i);
        m_out << "Track: " << step.trackId << "; Next " << step.nextTrackId << " direction " << step.directionToNext << "\n";
    }
}
