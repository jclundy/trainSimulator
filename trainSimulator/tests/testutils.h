#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "track_components/itracksegment.h"
#include "train/train.h"

// util functions
void printTrackInfo(ITrackSegment *track);
void printPosition(QPointF point);
void printTrainLocation(Train* train);

#endif // TEST_UTILS_H
