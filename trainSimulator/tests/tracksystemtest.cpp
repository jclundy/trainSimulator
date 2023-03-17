#include "tracksystemtest.h"
#include "testutils.h"
#include <QDebug>

TrackSystemTest::TrackSystemTest()
{
    m_trackSystem = new TrackSystem();
}

void TrackSystemTest::runTests() {
    testSetup();
//    testDrive1();
    testSignals();
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

    result = track4->connectFrontToTrack(track1);
    track4->getTrackGeometry()->setRotationAboutFront(120);
    qDebug() << "connected track4 front to junction 1" << result;


    LinearTrack* track5 = m_trackSystem->addLinearTrack();
    qDebug() << "added track" << track5->getId();


    result = track5->connectRearToTrack(track1);
    qDebug() << "connected track5 rear to junction 1" << result;
    track5->getTrackGeometry()->setRotationAboutRear(-120);

    qDebug() << "--------------------------------";
    printTrackSystemInfo();

    qDebug() << "--------------------------------";
    qDebug() << "Adding Signals";

    Signal* signal_0_rear = m_trackSystem->addSignal();
    signal_0_rear->placeOnTrackRear(track0);

    Signal* signal_0_front = m_trackSystem->addSignal();
    signal_0_front->placeOnTrackFront(track0);

    Signal* signal_2_rear = m_trackSystem->addSignal();
    signal_2_rear->placeOnTrackRear(track2);

    Signal* signal_2_front = m_trackSystem->addSignal();
    signal_2_front->placeOnTrackFront(track2);

    Signal* signal_3_rear = m_trackSystem->addSignal();
    signal_3_rear->placeOnTrackRear(track3);

    Signal* signal_3_front = m_trackSystem->addSignal();
    signal_3_front->placeOnTrackFront(track3);

    Signal* signal_4_front = m_trackSystem->addSignal();
    signal_4_front->placeOnTrackFront(track4);

    Signal* signal_4_rear = m_trackSystem->addSignal();
    signal_4_rear->placeOnTrackRear(track4);

    Signal* signal_5_rear = m_trackSystem->addSignal();
    signal_5_rear->placeOnTrackRear(track5);

    Signal* signal_5_front = m_trackSystem->addSignal();
    signal_5_front->placeOnTrackFront(track5);

}

void TrackSystemTest::testDrive1() {
    qDebug() << "================================";
    qDebug() << "Test Drive 1, from track 4, to junction 1, to track 2,3";
    Train* train = m_trackSystem->getTrainById(0);
    ITrackSegment* track4 = m_trackSystem->getTrackSegmentById(4);

    JunctionTrack* track1 = m_trackSystem->getJunctionById(1);

    track1->selectRearBranchById(4);
    track1->selectForwardBranchById(2);

    train->place(track4);
    train->setDesiredSpeed(3);


    qDebug() << "starting location";
    printTrainLocation(train);

    testDriving(100, 0.25);
}

void TrackSystemTest::testDriving(int iterations, float dt) {
    qDebug() << "---------------------------";
    qDebug() << "Driving trains in track system";

    bool stopped = false;
    int i = 0;
    for(i = 0; i < iterations && !stopped; i++) {
        m_trackSystem->driveTrains(dt);
        stopped = m_trackSystem->areAllTrainsStopped();

        qDebug() << "---------------------------";
        qDebug() << "iteration " << i;
        Train * train = m_trackSystem->getTrainById(0);
        printTrainLocation(train);
        qDebug() << "train speed: " << train->getSpeed();
    }

    qDebug() << "iterations: " << i << ", all trains stopped? " << stopped;

    for (int i = 0; i < m_trackSystem->getTrains().size(); i++) {
        Train* train = m_trackSystem->getTrains().at(i);
        qDebug() << "rail state of train ID=" << train->getId() << ": railState=" << train->getRailState();
    }

    qDebug() << "done driving train";

}

void TrackSystemTest::testSignals() {
    qDebug() << "===============================";
    qDebug() << "Testing signals";

    qDebug() << "Signals before initialization";
    printAllSignalInfo();

    m_trackSystem->driveSignals();
    qDebug() << "--------------------------------";
    qDebug() << "Signals after initialization";
    printAllSignalInfo();
    qDebug() << "--------------------------------";
    qDebug() << "Testing Junction switching";

    Signal* sig0 = (Signal *) m_trackSystem->getTrackSegmentById(0)->getFrontSignal();
    Signal* sig2 = (Signal *) m_trackSystem->getTrackSegmentById(2)->getRearSignal();
    Signal* sig4 = (Signal *) m_trackSystem->getTrackSegmentById(4)->getFrontSignal();
    Signal* sig5 = (Signal *) m_trackSystem->getTrackSegmentById(5)->getRearSignal();

    qDebug() << "Selecting rear branch track0 and forward branch track 2";
    JunctionTrack* track1 = m_trackSystem->getJunctionById(1);
    track1->selectRearBranchById(0);
    track1->selectForwardBranchById(2);

    printSignalInfo(sig0);
    printSignalInfo(sig2);
    printSignalInfo(sig4);
    printSignalInfo(sig5);
    qDebug() << "--------------------------------";

    qDebug() << "Selecting rear branch track4 and forward branch track 5";
    track1->selectRearBranchById(4);
    track1->selectForwardBranchById(5);

    printSignalInfo(sig0);
    printSignalInfo(sig2);
    printSignalInfo(sig4);
    printSignalInfo(sig5);

    qDebug() << "===============================";
    qDebug() << "testing signals by placing trains";
    qDebug() << "--------------------------------";
    Train* train0 = m_trackSystem->getTrainById(0);
    train0->stop();

    ITrackSegment * track0 = m_trackSystem->getTrackSegmentById(0);
    train0->place(track0);

    Train* train1 = m_trackSystem->addTrain();
    train1->place(track1);
    qDebug() << "placed trains on tracks 0 and 1";
    printAllSignalInfo();

    qDebug() << "--------------------------------";
    qDebug() << "placed trains on tracks 2 and 1";
    train0->place(track1);
    train1->place(m_trackSystem->getTrackSegmentById(2));
    printAllSignalInfo();

    qDebug() << "--------------------------------";
    qDebug() << "placed trains on tracks 2 and 3";
    train0->place(m_trackSystem->getTrackSegmentById(2));
    train1->place(m_trackSystem->getTrackSegmentById(3));
    printAllSignalInfo();



}

void TrackSystemTest::printAllSignalInfo() {
    for(int i = 0; i < m_trackSystem->getSignals().size(); i++) {
        printSignalInfo(m_trackSystem->getSignals().at(i));
    }
}

void TrackSystemTest::printTrackSystemInfo() {
    QList<ITrackSegment *> trackList = m_trackSystem->getTrackSegments();
    for (int i = 0; i < trackList.size(); i++) {
        printTrackInfo(trackList.at(i));
    }
}