#ifndef COLLISIONCHECKER_H
#define COLLISIONCHECKER_H

#include "track_components/itracksegment.h"
#include "train/ivehicle.h"

typedef struct {
    bool trainPresent;
    float trainSpeed;
    int trainId;
} train_speed_data;

static const train_speed_data default_train_speed_data = {
    .trainPresent = false,
    .trainSpeed = 0,
    .trainId = -1
};

class CollisionChecker
{
public:
    static bool collisionWillOccur(ITrackSegment* rearTrack, ITrackSegment* frontTrack);
    static bool collisionWillOccurInForwardDirection(ITrackSegment* rearTrack, ITrackSegment* frontTrack);
    static bool collisionWillOccurInReverseDirection(ITrackSegment* rearTrack, ITrackSegment* frontTrack);

    static bool trainBlockingForward(ITrackSegment* currentTrack);
    static bool trainBlockingRear(ITrackSegment* currentTrack);
    static bool collisionOccured(IVehicle* train1, IVehicle* train2);

    static train_speed_data getRearTrackTrainSpeed(ITrackSegment* rearTrack);
    static train_speed_data getFrontTrackTrainSpeed(ITrackSegment* frontTrack);
};

#endif // COLLISIONCHECKER_H
