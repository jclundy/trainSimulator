#include "collisionchecker.h"
#include <math.h>

bool CollisionChecker::collisionWillOccur(ITrackSegment* rearTrack, ITrackSegment* frontTrack) {

    track_sensor_data rearTrain = getSensorDataOfTrainClosestToFront(rearTrack);
    track_sensor_data frontTrain = getSensorDataOfTrainClosestToRear(frontTrack);

    if(rearTrain.trainPresent && frontTrain.trainPresent && rearTrain.trainId != frontTrain.trainId) {
        return rearTrain.trainSpeed> frontTrain.trainSpeed;
    }
    return false;
}

bool CollisionChecker::collisionWillOccurInForwardDirection(ITrackSegment* rearTrack, ITrackSegment* frontTrack) {
    track_sensor_data rearTrain = getSensorDataOfTrainClosestToFront(rearTrack);
    track_sensor_data frontTrain = getSensorDataOfTrainClosestToRear(frontTrack);

    if(rearTrain.trainPresent && frontTrain.trainPresent && rearTrain.trainId != frontTrain.trainId) {
        return rearTrain.trainSpeed> frontTrain.trainSpeed && rearTrain.trainSpeed > 0;
    }
    return false;
}

bool CollisionChecker::collisionWillOccurInReverseDirection(ITrackSegment* rearTrack, ITrackSegment* frontTrack) {
    track_sensor_data rearTrain = getSensorDataOfTrainClosestToFront(rearTrack);
    track_sensor_data frontTrain = getSensorDataOfTrainClosestToRear(frontTrack);

    if(rearTrain.trainPresent && frontTrain.trainPresent && rearTrain.trainId != frontTrain.trainId) {
        return rearTrain.trainSpeed> frontTrain.trainSpeed && frontTrain.trainSpeed < 0;
    }
    return false;
}

bool CollisionChecker::trainBlockingForward(ITrackSegment* currentTrack) {
    ITrackSegment* frontTrack = currentTrack->getSelectedForwardEnd();
    track_sensor_data frontTrain = getSensorDataOfTrainClosestToRear(frontTrack);

    if(frontTrain.trainPresent && frontTrain.trainSpeed <= 0) {
        return true;
    }
    return false;
}

bool CollisionChecker::trainBlockingRear(ITrackSegment* currentTrack) {
    ITrackSegment* rearTrack = currentTrack->getSelectedRearEnd();
    track_sensor_data rearTrain = getSensorDataOfTrainClosestToFront(rearTrack);

    if(rearTrain.trainPresent && rearTrain.trainSpeed >= 0) {
        return true;
    }
    return false;
}


track_sensor_data CollisionChecker::getSensorDataOfTrainClosestToFront(ITrackSegment* track) {
    track_sensor_data sensorData = default_track_sensor_data;

    if(track != NULL) {
        TrackSensor* sensor = track->getFrontSensor();
        if(sensor != NULL) {
            sensorData = sensor->getSensorData();
        }
    }

    return sensorData;
}

track_sensor_data CollisionChecker::getSensorDataOfTrainClosestToRear(ITrackSegment* track) {
    track_sensor_data sensorData = default_track_sensor_data;
    if(track != NULL) {
        TrackSensor* sensor = track->getRearSensor();
        if(sensor != NULL) {
            sensorData = sensor->getSensorData();
        }
    }
    return sensorData;
}

collision_info_t CollisionChecker::computeCollision(ITrackSegment* rearTrack, ITrackSegment* frontTrack, float extraDistanceFromRearToFront) {
    track_sensor_data rearTrain = getSensorDataOfTrainClosestToFront(rearTrack);
    track_sensor_data frontTrain = getSensorDataOfTrainClosestToRear(frontTrack);

    collision_info_t collisionData;
    collisionData.collisionWillOccur = false;
    collisionData.displacementOfForwardTrain = 0;
    collisionData.displacementOfRearTrain = 0;
    collisionData.timeTillCollision = -1;

    float rearLength = rearTrack->getLength();

    if(rearTrain.trainPresent && frontTrain.trainPresent && rearTrain.trainId != frontTrain.trainId) {

        if(rearTrain.trainSpeed> frontTrain.trainSpeed) {
            collisionData.collisionWillOccur = true;

            float p1 = rearTrain.positionOnTrack;
            float v1 = rearTrain.trainSpeed;

            float p2 = rearLength + extraDistanceFromRearToFront + frontTrain.positionOnTrack;
            float v2 = frontTrain.trainSpeed;

            float dt = -1;
            float epsilon = 0.001;
            // p1 + v1*dt = p2 + v2*dt
            // (p1 - p2)/(v2 - v1) = dt
            if(fabs(v2 - v1) > epsilon) {
                dt = (p1 - p2) / (v2 - v1);
            }
            collisionData.timeTillCollision = dt;
            collisionData.displacementOfForwardTrain = v2*dt;
            collisionData.displacementOfRearTrain = v1*dt;

        }
    }
    return collisionData;
}

collision_info_t CollisionChecker::computeCollision(track_sensor_data t1Data, float p1, track_sensor_data t2Data, float p2) {
    collision_info_t collisionData;
    collisionData.collisionWillOccur = false;
    collisionData.displacementOfForwardTrain = 0;
    collisionData.displacementOfRearTrain = 0;
    collisionData.timeTillCollision = -1;

    if(t1Data.trainPresent && t2Data.trainPresent && t1Data.trainId != t2Data.trainId) {

        float v1 = t1Data.trainSpeed;

        float v2 = t2Data.trainSpeed;

        float dt = -1;
        float epsilon = 0.001;
        // p1 + v1*dt = p2 + v2*dt
        // (p1 - p2)/(v2 - v1) = dt
        if(fabs(v2 - v1) > epsilon) {
            dt = (p1 - p2) / (v2 - v1);
        }
        collisionData.collisionWillOccur = dt > 0;
        collisionData.timeTillCollision = dt;
        collisionData.displacementOfForwardTrain = v2*dt;
        collisionData.displacementOfRearTrain = v1*dt;
    }
    return collisionData;
}
