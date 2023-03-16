#include "testutils.h"
#include <QDebug>
#include <math.h>

void printTrackInfo(ITrackSegment *track) {

    qDebug() << "ID " << track->getId();
    qDebug() << "length " << track->getTrackGeometry()->getLength();
    qDebug() << "center " << track->getTrackGeometry()->getCenter();
    qDebug() << "heading " << track->getTrackGeometry()->getHeading();

    qDebug() << "Front TrackEnd:";
    printPosition(track->getTrackGeometry()->getFrontEndPosition());

    qDebug() << "Rear TrackEnd:";
    printPosition(track->getTrackGeometry()->getRearEndPosition());
}

void printPosition(QPointF point) {
    qDebug() << "Position (x,y): (" << point.x() << "," << point.y() << ")";
}

void printTrainLocation(Train* train) {
    qDebug() << "Train world location" << train->getLocationInWorld();
    qDebug() << "Train track id: " << train->getFrontLocation().getTrackId() << ", " << train->getFrontLocation().getPositionOnTrack() << " meters from track rear";
}

