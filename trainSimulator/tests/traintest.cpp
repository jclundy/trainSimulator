#include "traintest.h"

#include <QDebug>

TrainTest::TrainTest()
{
    m_train = NULL;
}

void TrainTest::runTests() {
    testCreateTrain();
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

    TrackSegment* track0 = new TrackSegment();
    printTrackInfo(track0);
    m_trackList.push_back(track0);

    TrackEnd* front = track0->getForwardEnd();
    qDebug() << "front's parent is track0 " << (front->getParentTrackSegment() == track0);
    TrackEnd* rear = track0->getRearEnd();
    qDebug() << "rear's parent is track0 " << (rear->getParentTrackSegment() == track0);

    // translate
    track0->setCenter(QPointF(30,30));
    qDebug() << "Moved track";
    printTrackInfo(track0);

    // rotate
    track0->setRotationAboutCenter(90);
    qDebug() << "Rotated about center";
    printTrackInfo(track0);

    track0->setRotationAboutFront(45);
    qDebug() << "Rotated about front";
    printTrackInfo(track0);

    track0->setRotationAboutRear(45);
    qDebug() << "Rotated about rear";
    printTrackInfo(track0);

}

void TrainTest::testCleanup() {
    qDebug() << "=========== Test cleanup ==============";

    qDebug() << "train is not null " << (m_train != NULL);

    delete m_train;
    qDebug() << "train deleted " << (m_train == NULL);
}
