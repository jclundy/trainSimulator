#ifndef COLLISIONCHECKER_H
#define COLLISIONCHECKER_H

#include "track_components/itracksegment.h"
#include "train/ivehicle.h"
#include "track_components/tracksensor.h"


class CollisionChecker
{
public:
    static bool collisionWillOccur(ITrackSegment* rearTrack, ITrackSegment* frontTrack);
    static bool collisionWillOccurInForwardDirection(ITrackSegment* rearTrack, ITrackSegment* frontTrack);
    static bool collisionWillOccurInReverseDirection(ITrackSegment* rearTrack, ITrackSegment* frontTrack);

    static bool trainBlockingForward(ITrackSegment* currentTrack);
    static bool trainBlockingRear(ITrackSegment* currentTrack);
    static bool collisionOccured(IVehicle* train1, IVehicle* train2);

    static track_sensor_data getSensorDataOfTrainClosestToFront(ITrackSegment* track);
    static track_sensor_data getSensorDataOfTrainClosestToRear(ITrackSegment* track);
};

#endif // COLLISIONCHECKER_H
