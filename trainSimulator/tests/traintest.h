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
    void testDriving(float speed = 4, int iterations = 100, float dt=0.5);
    void testCleanup();
    void testJunctionPath1DerailingForward();
    void testJunctionPath1SuccessForward();
    void testJunctionPath1SuccessReverse();
    void testJunctionPath1DerailingReverse();

    void testJunctionPath2SuccessForward();
    void testJunctionPath2SuccessReverse();

    void runTests();

    QList<ITrackSegment*> m_trackList;
    Train* m_train;

    // util functions
    void printTrackInfo(ITrackSegment *track);
    void printPosition(QPointF point);
    void printTrainLocation(Train* train);
};

#endif // TEST1_H
