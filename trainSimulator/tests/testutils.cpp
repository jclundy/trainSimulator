#include "traintest.h"
#include <QDebug>

void TrainTest::printTrackInfo(TrackSegment *track) {

    qDebug() << "length " << track->getLength();
    qDebug() << "center " << track->getCenter();
    qDebug() << "heading " << track->getHeading();

    qDebug() << "Front TrackEnd:";
    TrackEnd* front = track->getForwardEnd();
    printPosition(front->m_position);

    qDebug() << "Rear TrackEnd:";
    TrackEnd* rear = track->getRearEnd();
    printPosition(rear->m_position);
}

void TrainTest::printTrackEndInfo(TrackEnd *end) {

    printPosition(end->m_position);
    qDebug() << "Pole " << end->m_pole;
    qDebug() << "Is Front " << end->isFront();
    qDebug() << "Is Rear " << end->isRear();
    qDebug() << "Is Fork " << end->isFork();
    qDebug() << "num connections" << end->m_neighbourList.size();
}

void TrainTest::printPosition(QPointF point) {
    qDebug() << "Position (x,y): (" << point.x() << "," << point.y() << ")";
}
