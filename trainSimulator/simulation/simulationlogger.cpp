#include "simulationlogger.h"

SimulationLogger::SimulationLogger(QString fileName, Simulation* simulation)
{
    m_fileName = fileName;
    m_simulation = simulation;

    m_file = new QFile(fileName);
    if (m_file->open(QIODevice::WriteOnly | QIODevice::Text)) {
        m_out = new QTextStream(m_file);
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
void SimulationLogger::logChangedSignals() {

}

void SimulationLogger::logChangedJunctions() {

}

// logging for individual components
void SimulationLogger::logTrackInfo(ITrackSegment *track) {

}

void SimulationLogger::logSignalInfo(Signal* signal) {

}

void SimulationLogger::logJunctionInfo(Junction* junction) {

}

void logTrainInfo(Train* train) {

}
