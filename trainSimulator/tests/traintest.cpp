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
    testCreateJunctionTrack();

//    testJunctionPath1DerailingForward();
//    testJunctionPath1SuccessForward();
//    testJunctionPath1SuccessReverse();
//    testJunctionPath1DerailingReverse();

    testJunctionPath2SuccessForward();
    testJunctionPath2SuccessReverse();

    testCleanup();
}

void TrainTest::testCreateTrain() {
    qDebug() << "=========== Test setup ==============";
    m_train = new Train(0);

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
    m_trackList.push_back(track3);

    ITrackSegment* track2 = m_trackList.at(2);
    bool success = track3->connectRearToTrack(track2);
    qDebug() << "attached track3's rear to track2's front"  << success;
    printTrackInfo(track3);

    // create more track segments
    LinearTrack* track4 = new LinearTrack(4);
    m_trackList.push_back(track4);

    LinearTrack* track5 = new LinearTrack(5, 30);
    m_trackList.push_back(track5);

    LinearTrack* track6 = new LinearTrack(6, 30);
    m_trackList.push_back(track6);

    JunctionTrack* track7 = new JunctionTrack(7);
    m_trackList.push_back(track7);

    LinearTrack* track8 = new LinearTrack(8);
    m_trackList.push_back(track8);

    qDebug() << "---------------------------";
    bool result1 = track7->connectFrontToTrack(track3);
    bool result2 = track7->connectRearToTrack(track3);
    qDebug() << "tried connecting junction front to junction rear " <<  result1;
    qDebug() << "tried connecting junction rear to junction front " <<  result2;

    qDebug() << "---------------------------";
    bool result = track4->connectRearToTrack(track3);
    qDebug() << "attached track4 rear to junction3's front" <<  result;
    printTrackInfo(track4);
    result = track5->connectRearToTrack(track3);

    qDebug() << "---------------------------";
    qDebug() << "attached track5 rear to junction3's front" <<  result;
    track5->getTrackGeometry()->setRotationAboutRear(160);
    printTrackInfo(track5);
    result = track6->connectRearToTrack(track5);

    qDebug() << "---------------------------";
    qDebug() << "attached track6 rear to track5's front" <<  result;
    track6->getTrackGeometry()->setRotationAboutRear(200);
    printTrackInfo(track6);

    // attach junction [7] to 6
    result = track7->connectRearToTrack(track6);

    qDebug() << "---------------------------";
    qDebug() << "attached track6 front to junction 7's rear" <<  result;
    printTrackInfo(track7);
    // attach 4 to junction [7]
    result = track4->connectFrontToTrack(track7);

    qDebug() << "---------------------------";
    qDebug() << "attached track4 front to junction 7's rear" <<  result;
    printTrackInfo(track4);

    result = track8->connectRearToTrack(track7);

    qDebug() << "---------------------------";
    qDebug() << "attached track8 rear to junction 7's front" <<  result;
    printTrackInfo(track8);

    qDebug() << "---------------------------";
    qDebug() << "junction 3 selected rear track id " << track3->getSelectedRearEnd()->getId();
    qDebug() << "junction 3 selected forward track id " << track3->getSelectedForwardEnd()->getId();

    qDebug() << "junction 7 selected rear track id " << track7->getSelectedRearEnd()->getId();
    qDebug() << "junction 7 selected forward track id " << track7->getSelectedForwardEnd()->getId();

}

void TrainTest::testDriving(float speed, int iterations, float dt) {
    qDebug() << "---------------------------";
    qDebug() << "Driving train";
    m_train->stop();

    m_train->setDesiredSpeed(speed);

    qDebug() << "starting location";
    printTrainLocation(m_train);
    qDebug() << "---------------------------";

    bool success = true;
    int i;
    for(i = 0; i < iterations && success; i++) {
        success = m_train->drive(dt);
        if(i % 5 == 0) {
            qDebug() << "---------------------------";
            qDebug() << "iteration " << i;
            printTrainLocation(m_train);
            qDebug() << "train speed: " << m_train->m_speed;
        }
    }
    if(!success) {
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

void TrainTest::testJunctionPath1DerailingForward() {
    m_train->place(m_trackList.at(0));
    qDebug() << "==============================";
    qDebug() << "first junction path 1 forward derailing";
    testDriving();
}

void TrainTest::testJunctionPath1SuccessForward() {
    m_train->stop();

    qDebug() << "==============================";
    qDebug() << "first junction path 1 forward";

    m_train->place(m_trackList.at(0));
    JunctionTrack* track7 = (JunctionTrack*) m_trackList.at(7);
    bool success = track7->selectRearBranchById(4);
    qDebug() << "Set track7 rear branch to 4; success=" << success;

    testDriving();
}

void TrainTest::testJunctionPath1SuccessReverse() {
    m_train->stop();
    m_train->place(m_trackList.at(8));

    JunctionTrack* track7 = (JunctionTrack*) m_trackList.at(7);
    track7->selectRearBranchById(4);

    JunctionTrack* track3 = (JunctionTrack*) m_trackList.at(3);
    track3->selectForwardBranchById(4);

    qDebug() << "==============================";
    qDebug() << "test junction path 1 reversing";
    testDriving(-4);
}

void TrainTest::testJunctionPath1DerailingReverse() {
    m_train->stop();
    m_train->place(m_trackList.at(8));


    JunctionTrack* track7 = (JunctionTrack*) m_trackList.at(7);
    track7->selectRearBranchById(4);
    JunctionTrack* track3 = (JunctionTrack*) m_trackList.at(3);
    track3->selectForwardBranchById(5);
    qDebug() << "==============================";
    qDebug() << "test junction path 1 reversing and derailing";
    testDriving(-4);
}

void TrainTest::testJunctionPath2SuccessForward() {
    m_train->stop();
    m_train->place(m_trackList.at(0));


    JunctionTrack* track7 = (JunctionTrack*) m_trackList.at(7);
    track7->selectRearBranchById(6);
    JunctionTrack* track3 = (JunctionTrack*) m_trackList.at(3);
    track3->selectForwardBranchById(5);
    qDebug() << "==============================";
    qDebug() << "test junction path 2 forward";
    testDriving(4);
}

void TrainTest::testJunctionPath2SuccessReverse() {
    m_train->stop();
    m_train->place(m_trackList.at(8));


    JunctionTrack* track7 = (JunctionTrack*) m_trackList.at(7);
    track7->selectRearBranchById(6);
    JunctionTrack* track3 = (JunctionTrack*) m_trackList.at(3);
    track3->selectForwardBranchById(5);
    qDebug() << "==============================";
    qDebug() << "test junction path 2 reversing";
    testDriving(-4);
}
