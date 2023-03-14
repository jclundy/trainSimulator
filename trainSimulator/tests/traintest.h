#ifndef TEST1_H
#define TEST1_H

#include <QList>
#include <QPointF>
#include "lineartrack.h"
#include "train.h"

class TrainTest : QObject
{
Q_OBJECT

public:
    TrainTest();

    void testCreateTrain();
    void testCreateTrackSegment();
    void testDriving();
    void testCleanup();

    void runTests();

    QList<LinearTrack*> m_trackList;
    Train* m_train;

    // util functions
    void printTrackInfo(LinearTrack *track);
    void printTrackEndInfo(TrackEnd *end);
    void printPosition(QPointF point);
    void printTrainLocation(Train* train);
};

#endif // TEST1_H
