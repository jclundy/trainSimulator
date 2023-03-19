#include "simulationlogger.h"
#include <QDebug>

SimulationLogger::SimulationLogger(QString fileName, Simulation* simulation)
{
    m_fileName = fileName;
    m_simulation = simulation;

    m_file = new QFile(fileName);
    if (m_file->open(QIODevice::WriteOnly | QIODevice::Text)) {
            m_out.setDevice(m_file);
    }
}


// high-level logging
void SimulationLogger::logTrackSystemInfo() {

}

void SimulationLogger::logTrainPaths() {

}

void SimulationLogger::logAllTrains() {

}

void SimulationLogger::logAllSignals() {

}

void SimulationLogger::logAllJunctions() {

}

void SimulationLogger::logTimeStep() {
    logAllTrains();
    logAllSignals();
    logAllJunctions();

    // todo - change to log signal changes and junction changes
}

// logging changed track elements
void SimulationLogger::logTrainMovements() {
    // logTrainMovements
}

void SimulationLogger::logChangedSignals() {

}

void SimulationLogger::logChangedJunctions() {

}

// logging for individual components
void SimulationLogger::logTrackInfo(ITrackSegment *track) {
    m_out << "ID " << track->getId() << "\n";
    m_out << "length " << track->getTrackGeometry()->getLength() << "\n";
    m_out << "heading " << track->getTrackGeometry()->getHeading() << "\n";
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
        m_out << "\n";
    }
}

void SimulationLogger::logSignalInfo(Signal* signal) {
    QString color = (signal->isRed())? "RED" : "GREEN";

    ITrackSegment *track = signal->getTrackSegment();
    if(track != NULL) {
        QString placementStr = "";
        auto placement = signal->getPlacement();
        if(placement == SIGNAL_TRACK_FRONT) {
            placementStr = "Front";
        } else if (placement == SIGNAL_TRACK_REAR) {
            placementStr = "Rear";
        }

        m_out << "Signal ID" << signal->getId() << "on Track " << track->getId() << placementStr << "; state=" << color  << "\n";
    } else {
        m_out << "Signal ID" << signal->getId() << "not placed" << "; state=" << color  << "\n";
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
    m_out << "Train ID: " << train->getId() << "\n";
    m_out << "Train speed: " << train->getSpeed();
    m_out << "Train front world location";
    logPoint(train->getFrontLocationInWorld());
    m_out << "\n";
    m_out << "Train track id: " << train->getFrontLocation().getTrackId() << ", " << train->getFrontLocation().getPositionOnTrack() << " meters from track rear"  << "\n";

}
