#ifndef SIMULATIONLOGGER_H
#define SIMULATIONLOGGER_H

#include <QTextStream>
#include <QFile>
#include "track_system/tracksystem.h"
#include "track_system/systemcontroller.h"
#include "simulation.h"

class SimulationLogger
{
    SimulationLogger(QString fileName, Simulation* simulation);
public:
    // high-level logging
    void logTrackSystemInfo();
    void logTrainPaths();
    void logAllTrains();
    void logAllSignals();
    void logAllJunctions();

    void logTimeStep();

    // logging changed track elements
    void logChangedSignals();
    void logChangedJunctions();

    // logging for individual components
    void logTrackInfo(ITrackSegment *track);
    void logSignalInfo(Signal* signal);
    void logJunctionInfo(Junction* junction);
    void logTrainInfo(Train* train);

private:
    QFile *m_file;
    QString m_fileName;
    QTextStream *m_out;
    Simulation* m_simulation;
};

#endif // SIMULATIONLOGGER_H
