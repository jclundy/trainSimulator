#include "collisionchecker.h"

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
