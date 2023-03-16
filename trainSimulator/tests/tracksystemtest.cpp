#include "tracksystemtest.h"
#include <QDebug>

TrackSystemTest::TrackSystemTest()
{
    m_trackSystem = new TrackSystem();
}


void TrackSystemTest::testSetup() {
    Train* train0 = m_trackSystem->addTrain();
    qDebug() << "added train " << train0->getId();

    LinearTrack* track0 = m_trackSystem->addLinearTrack();
}

void TrackSystemTest::testDriving() {

}

void TrackSystemTest::testSignals() {

}
