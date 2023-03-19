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
    void logAllTracks();
    void logAllSignals();
    void logAllJunctions();
    void logAllTrains();

    void logTrainPaths();

    void logTimeStep();

    // logging changed track elements
    void logTrainMovements();
    void logChangedSignals();
    void logChangedJunctions();

    // logging for individual components
    void logTrackInfo(ITrackSegment *track);
    void logSignalInfo(Signal* signal);
    void logJunctionInfo(JunctionTrack* track);
    void logTrainInfo(Train* train);
    void logTrainMovementInfo(Train* train);

    void logTrackPath(QList<path_step> pathList);

    // logging utils
    void logPoint(QPointF point);
    void logNeighbours(QList<ITrackSegment*> list);


private:
    QFile *m_file;
    QString m_fileName;
    QTextStream m_out;
    Simulation* m_simulation;
};

#endif // SIMULATIONLOGGER_H
