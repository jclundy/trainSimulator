#ifndef COLLISIONCHECKER_H
#define COLLISIONCHECKER_H

#include "track_components/itracksegment.h"
#include "train/ivehicle.h"
#include "track_components/tracksensor.h"

typedef struct {
    bool collisionWillOccur;
    float timeTillCollision;
    float displacementOfRearTrain;
    float displacementOfForwardTrain;
} collision_info_t;

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

    static collision_info_t computeCollision(ITrackSegment* rearTrack, ITrackSegment* frontTrack, float extraDistanceFromRearToFront=0);
    static collision_info_t computeCollision(track_sensor_data t1Data, float p1, track_sensor_data t2Data, float p2);

};

#endif // COLLISIONCHECKER_H
