#include "testutils.h"
#include <QDebug>
#include <math.h>

void printTrackInfo(ITrackSegment *track) {

    qDebug() << "ID " << track->getId();
    qDebug() << "length " << track->getTrackGeometry()->getLength();
    qDebug() << "heading " << track->getTrackGeometry()->getHeading();

    qDebug() << "Rear: " << track->getTrackGeometry()->getRearEndPosition();

    qDebug() << "Front:" << track->getTrackGeometry()->getFrontEndPosition();

}

void printPosition(QPointF point) {
    qDebug() << "Position (x,y): (" << point.x() << "," << point.y() << ")";
}

void printTrainLocation(Train* train) {
    qDebug() << "Train world location" << train->getLocationInWorld();
    qDebug() << "Train track id: " << train->getFrontLocation().getTrackId() << ", " << train->getFrontLocation().getPositionOnTrack() << " meters from track rear";
}

void printSignalInfo(Signal* signal) {
    ITrackSegment *track = signal->getTrackSegment();
    if(track != NULL) {
        qDebug() << "Signal ID" << signal->getId() << " on Track " << track->getId();
    } else {
        qDebug() << "Signal ID" << signal->getId() << " not placed";
    }
    if(signal->isRed()) {
        qDebug() << "Signal is RED";
    } else {
        qDebug() << "Signal is GREEN";
    }
}

