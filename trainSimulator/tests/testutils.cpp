#include "traintest.h"
#include <QDebug>
#include <math.h>

void TrainTest::printTrackInfo(LinearTrack *track) {

    qDebug() << "ID " << track->getId();
    qDebug() << "length " << track->getLength();
    qDebug() << "center " << track->getCenter();
    qDebug() << "heading " << track->getHeading();

    qDebug() << "Front TrackEnd:";
    TrackEnd* front = track->getForwardEnd();
    printPosition(front->m_position);

    qDebug() << "Rear TrackEnd:";
    TrackEnd* rear = track->getRearEnd();
    printPosition(rear->m_position);

    QPointF diff = front->m_position - rear->m_position;
    float length = sqrt(pow(diff.x(),2) + pow(diff.y(),2));
    qDebug() << "computed length: " << length;


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

void TrainTest::printTrainLocation(Train* train) {
    qDebug() << "Train world location" << train->getLocationInWorld();
    qDebug() << "Train track id: " << train->frontLocation.getTrackId() << ", " << train->frontLocation.getPositionOnTrack() << " meters from track rear";
}

