#ifndef SIMULATIONLOGGER_H
#define SIMULATIONLOGGER_H

#include <QTextStream>
#include <QFile>
#include "track_system/tracksystem.h"
#include "track_system/systemcontroller.h"

class SimulationLogger
{
public:

    SimulationLogger(QString fileName);
    void setTrackSystem(TrackSystem* trackSystem);
    void setTrainPaths(QMap<unsigned int, TrackPathTable*> trainPaths);
    void openFile();
    void closeFile();


    // high-level logging
    void logTrackSystemInfo();
    void logAllTracks();
    void logAllSignals();
    void logAllJunctions();
    void logAllTrains();

    void logTrainPaths();

    void logTimeStep(int iterations, float elapsedSeconds);

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
    TrackSystem* m_trackSystem;
    QMap<unsigned int, TrackPathTable*> m_trainPaths;

};

#endif // SIMULATIONLOGGER_H
