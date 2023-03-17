#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "track_components/itracksegment.h"
#include "train/train.h"
#include "track_system/signal.h"

// util functions
void printTrackInfo(ITrackSegment *track);
void printPosition(QPointF point);
void printTrainLocation(Train* train);
void printSignalInfo(Signal* signal);

#endif // TEST_UTILS_H
