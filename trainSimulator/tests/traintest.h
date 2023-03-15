#ifndef TEST1_H
#define TEST1_H

#include <QList>
#include <QPointF>
#include "track_components/itracksegment.h"
#include "train/train.h"

class TrainTest : QObject
{
Q_OBJECT

public:
    TrainTest();

    void testCreateTrain();
    void testCreateTrackSegment();
    void testCreateJunctionTrack();
    void testDriving(int iterations = 100, float dt=0.5);
    void testCleanup();
    void testJunctionDerailingForward();
    void testJunctionSuccessForward();

    void runTests();

    QList<ITrackSegment*> m_trackList;
    Train* m_train;

    // util functions
    void printTrackInfo(ITrackSegment *track);
    void printPosition(QPointF point);
    void printTrainLocation(Train* train);
};

#endif // TEST1_H
