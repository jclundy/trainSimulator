#ifndef TRACKSYSTEM_H
#define TRACKSYSTEM_H

#include "track_components/itracksegment.h"
#include "track_components/lineartrack.h"
#include "track_components/junctiontrack.h"
#include "train/train.h"

class TrackSystem
{
public:
    TrackSystem(unsigned int maxForksPerJunction = 2, int defaultTrackLength = 20);

    // drivers
    void driveJunctions();
    void driveSignals();
    void driveTrains(float dt);

    // getters
    QList<Train*> getTrains();
    QList<JunctionTrack*> getJunctions();
    QList<ITrackSegment*> getTrackSegments();
    //QList<Signals*> getSignals();

    Train* getTrainById();
    JunctionTrack* getJunctionById();
    ITrackSegment* getTrackSegmentById();

    // adders
    Train* addTrain();
    LinearTrack* addLinearTrack();
    JunctionTrack* addJunctionTrack();
//    Signal* addSignal();

private:

    // configuration parameters
    unsigned int m_maxForksPerJunction;
    unsigned int m_defaultTrackLength;

    // ids
    unsigned int m_nextAvailableTrackId;
    unsigned int m_nextAvailableTrainId;
    unsigned int m_nextAvailableSignalId;

    QList<ITrackSegment*> m_trackSegments;
    QList<JunctionTrack*> m_junctions;
    QList<Train*> m_trains;

    // QList<Signal*> m_signals;


};

#endif // TRACKSYSTEM_H
