#ifndef TEST1_H
#define TEST1_H

#include <QList>
#include "tracksegment.h"
#include "train.h"

class Test1 : QObject
{
Q_OBJECT

public:
    Test1();

    void testSetup();
    void testDriving();
    void cleanup();

    QList<TrackSegment*> m_trackList;
    Train* m_train;
};

#endif // TEST1_H
