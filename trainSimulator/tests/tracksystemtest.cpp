#include "tracksystemtest.h"
#include "testutils.h"
#include <QDebug>

TrackSystemTest::TrackSystemTest()
{
    m_trackSystem = new TrackSystem();
}

void TrackSystemTest::testSetup() {
    Train* train0 = m_trackSystem->addTrain();
    qDebug() << "added train " << train0->getId();

    LinearTrack* track0 = m_trackSystem->addLinearTrack();
    track0->getTrackGeometry()->translateRearPosition(QPointF(0,0));
    qDebug() << "added track" << track0->getId();

    JunctionTrack* track1 = m_trackSystem->addJunctionTrack();
    qDebug() << "added track" << track1->getId();

    qDebug() << "added junction track " << track1->getId();
    bool result = track1->connectRearToTrack(track0);
    qDebug() << "connected junction 1 rear to track0 " << result;

    LinearTrack* track2 = m_trackSystem->addLinearTrack();
    qDebug() << "added track" << track2->getId();

    result = track2->connectRearToTrack(track1);
    qDebug() << "connected track2 rear to junction 1 " << result;

    LinearTrack* track3 = m_trackSystem->addLinearTrack();
    qDebug() << "added track" << track3->getId();

    result = track3->connectRearToTrack(track2);
    qDebug() << "connected track3 rear to track2" << result;

    // other forks
    LinearTrack* track4 = m_trackSystem->addLinearTrack();
    qDebug() << "added track" << track4->getId();

    track4->getTrackGeometry()->translateRearPosition(QPointF(0, -10));
    result = track4->connectFrontToTrack(track1);
    qDebug() << "connected track4 front to junction 1" << result;

    LinearTrack* track5 = m_trackSystem->addLinearTrack();
    qDebug() << "added track" << track5->getId();

    QPointF track1Front = track1->getTrackGeometry()->getFrontEndPosition();
    QPointF track5Front = track1Front + QPointF(15, -10);
    track5->getTrackGeometry()->translateForwardPosition(track5Front);

    result = track5->connectRearToTrack(track1);
    qDebug() << "connected track5 rear to junction 1" << result;

    qDebug() << "--------------------------------";
    printTrackSystemInfo();
    qDebug() << "================================";

}

void TrackSystemTest::testDriving() {

}

void TrackSystemTest::testSignals() {

}

void TrackSystemTest::printTrackSystemInfo() {
    QList<ITrackSegment *> trackList = m_trackSystem->getTrackSegments();
    for (int i = 0; i < trackList.size(); i++) {
        printTrackInfo(trackList.at(i));
    }
}
