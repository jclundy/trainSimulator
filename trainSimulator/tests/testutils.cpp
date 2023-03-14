#include "traintest.h"
#include <QDebug>
#include <math.h>

void TrainTest::printTrackInfo(LinearTrack *track) {

    qDebug() << "ID " << track->getId();
    qDebug() << "length " << track->getLength();
    qDebug() << "center " << track->getCenter();
    qDebug() << "heading " << track->getHeading();

    qDebug() << "Front TrackEnd:";
    printPosition(track->getFrontEndPosition());

    qDebug() << "Rear TrackEnd:";
    printPosition(track->getRearEndPosition());
}

void TrainTest::printPosition(QPointF point) {
    qDebug() << "Position (x,y): (" << point.x() << "," << point.y() << ")";
}

void TrainTest::printTrainLocation(Train* train) {
    qDebug() << "Train world location" << train->getLocationInWorld();
    qDebug() << "Train track id: " << train->frontLocation.getTrackId() << ", " << train->frontLocation.getPositionOnTrack() << " meters from track rear";
}

