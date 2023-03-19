#include "simulationlogger.h"
#include <QDebug>

SimulationLogger::SimulationLogger(QString fileName, Simulation* simulation)
{
    m_fileName = fileName;
    m_simulation = simulation;

    m_file = new QFile(fileName);
//    if (m_file->open(QIODevice::WriteOnly | QIODevice::Text)) {
//        m_out = new QTextStream(m_file);
//    }
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
}

void SimulationLogger::logJunctionInfo(Junction* junction) {

}

void logTrainInfo(Train* train) {

}
