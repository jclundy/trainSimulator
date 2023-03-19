#ifndef SIMULATIONLOGGER_H
#define SIMULATIONLOGGER_H

#include <QTextStream>
#include "track_system/tracksystem.h"
#include "track_system/systemcontroller.h"

class SimulationLogger
{
    SimulationLogger(QTextStream out);
public:
    // high-level logging
    void logTrackSystemInfo(TrackSystem* system);
    void logTrainPaths(SystemController* system);

    // logging for individual components
    void logTrackInfo(ITrackSegment *track);
    void logSignalInfo(Signal* signal);
    void logJunctionInfo(Junction* junction);
    void logTrainInfo(Train* train);

private:
    QTextStream m_out;
};

#endif // SIMULATIONLOGGER_H
