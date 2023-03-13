#ifndef TEST1_H
#define TEST1_H

#include <QList>
#include <QPointF>
#include "tracksegment.h"
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

    QList<TrackSegment*> m_trackList;
    Train* m_train;

    // util functions
    void printTrackInfo(TrackSegment *track);
    void printTrackEndInfo(TrackEnd *end);
    void printPosition(QPointF point);
};

#endif // TEST1_H
