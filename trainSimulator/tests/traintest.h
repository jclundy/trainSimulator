#ifndef TEST1_H
#define TEST1_H

#include <QList>
#include "tracksegment.h"
#include "train.h"

class TrainTest : QObject
{
Q_OBJECT

public:
    TrainTest();

    void testCreateTrain();
    void testDriving();
    void testCleanup();

    void runTests();

    QList<TrackSegment*> m_trackList;
    Train* m_train;
};

#endif // TEST1_H
