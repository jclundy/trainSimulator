#include "traintest.h"
#include "track_components/junctiontrack.h"
#include <QDebug>

TrainTest::TrainTest()
{
    m_train = NULL;
}

void TrainTest::runTests() {
    testCreateTrain();
    testCreateTrackSegment();
//    testDriving();
    testCreateJunctionTrack();

    testCleanup();
}

void TrainTest::testCreateTrain() {
    qDebug() << "=========== Test setup ==============";
    m_train = new Train();

    qDebug() << "Created train";
    qDebug() << "length: " << m_train->m_length;
    qDebug() << "speed: " << m_train->m_speed;
    qDebug() << "speed setpoint: " << m_train->m_speedSetpoint;
    qDebug() << "acceleration: " << m_train->m_acceleration;

    qDebug() << "control model is null: " << (m_train->m_controlModel == NULL);
}

void TrainTest::testCreateTrackSegment() {
    qDebug() << "=========== Test create track segment ==============";

    LinearTrack* track0 = new LinearTrack(0);
    printTrackInfo(track0);
    m_trackList.push_back(track0);

    // translate
    track0->getTrackGeometry()->setCenter(QPointF(30,30));
    qDebug() << "---------------------------";
    qDebug() << "Moved track";
    printTrackInfo(track0);

    // rotate
    track0->getTrackGeometry()->setRotationAboutCenter(90);
    qDebug() << "---------------------------";
    qDebug() << "Rotated about center";
    printTrackInfo(track0);

    track0->getTrackGeometry()->setRotationAboutFront(45);
    qDebug() << "---------------------------";
    qDebug() << "Rotated about front";
    printTrackInfo(track0);

    track0->getTrackGeometry()->setRotationAboutRear(120);
    qDebug() << "---------------------------";
    qDebug() << "Rotated about rear";
    printTrackInfo(track0);

    qDebug() << "=========== Test 2nd track segment ==============";

    LinearTrack* track1 = new LinearTrack(1);
    m_trackList.push_back(track1);

    bool success = track0->connectFrontToTrack(track1);
    qDebug() << "attached track0's front to track1's rear " << success;
    printTrackInfo(track1);
    printTrackInfo(track0);

    LinearTrack* track2 = new LinearTrack(2);
    m_trackList.push_back(track2);
    qDebug() << "---------------------------";
    success = track2->connectRearToTrack(track1);
    qDebug() << "attached track1's rear to track2's front"  << success;
    printTrackInfo(track2);

}

void TrainTest::testCreateJunctionTrack() {
    qDebug() << "=========== Test create junction track ==============";

    JunctionTrack* track3 = new JunctionTrack(3);

    ITrackSegment* track2 = m_trackList.at(2);
    bool success = track3->connectRearToTrack(track2);
    qDebug() << "attached track3's rear to track2's front"  << success;
    printTrackInfo(track3);

}

void TrainTest::testDriving() {
    qDebug() << "=========== Test driving train ==============";
    m_train->place(m_trackList.at(0));
    qDebug() << "placed train on track0";

    float dt = 0.5; // seconds

    qDebug() << "starting location";
    printTrainLocation(m_train);
    qDebug() << "---------------------------";

    m_train->setDesiredSpeed(3);
    bool success = true;
    for(int i = 0; i < 40 && success; i++) {
        success = m_train->drive(dt);
        qDebug() << "---------------------------";
        qDebug() << "iteration " << i;
        printTrainLocation(m_train);
        qDebug() << "train speed: " << m_train->m_speed;
    }
    qDebug() << "accident free? " << success;
    qDebug() << "done driving train";

}

void TrainTest::testCleanup() {
    qDebug() << "=========== Test cleanup ==============";

    qDebug() << "train is not null " << (m_train != NULL);

    delete m_train;
    qDebug() << "train deleted " << (m_train == NULL);
}
