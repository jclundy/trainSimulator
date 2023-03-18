#include "collisionchecker.h"

bool CollisionChecker::collisionWillOccur(ITrackSegment* rearTrack, ITrackSegment* frontTrack) {

    train_speed_data rearTrain = getSpeedOfTrainClosestToFront(rearTrack);
    train_speed_data frontTrain = getSpeedOfTrainClosestToRear(frontTrack);

    if(rearTrain.trainPresent && frontTrain.trainPresent && rearTrain.trainId != frontTrain.trainId) {
        return rearTrain.trainSpeed> frontTrain.trainSpeed;
    }
    return false;
}

bool CollisionChecker::collisionWillOccurInForwardDirection(ITrackSegment* rearTrack, ITrackSegment* frontTrack) {
    train_speed_data rearTrain = getSpeedOfTrainClosestToFront(rearTrack);
    train_speed_data frontTrain = getSpeedOfTrainClosestToRear(frontTrack);

    if(rearTrain.trainPresent && frontTrain.trainPresent && rearTrain.trainId != frontTrain.trainId) {
        return rearTrain.trainSpeed> frontTrain.trainSpeed && rearTrain.trainSpeed > 0;
    }
    return false;
}

bool CollisionChecker::collisionWillOccurInReverseDirection(ITrackSegment* rearTrack, ITrackSegment* frontTrack) {
    train_speed_data rearTrain = getSpeedOfTrainClosestToFront(rearTrack);
    train_speed_data frontTrain = getSpeedOfTrainClosestToRear(frontTrack);

    if(rearTrain.trainPresent && frontTrain.trainPresent && rearTrain.trainId != frontTrain.trainId) {
        return rearTrain.trainSpeed> frontTrain.trainSpeed && frontTrain.trainSpeed < 0;
    }
    return false;
}

bool CollisionChecker::trainBlockingForward(ITrackSegment* currentTrack) {
    ITrackSegment* frontTrack = currentTrack->getSelectedForwardEnd();
    train_speed_data frontTrain = getSpeedOfTrainClosestToRear(frontTrack);

    if(frontTrain.trainPresent && frontTrain.trainSpeed <= 0) {
        return true;
    }
    return false;
}

bool CollisionChecker::trainBlockingRear(ITrackSegment* currentTrack) {
    ITrackSegment* rearTrack = currentTrack->getSelectedRearEnd();
    train_speed_data rearTrain = getSpeedOfTrainClosestToFront(rearTrack);

    if(rearTrain.trainPresent && rearTrain.trainSpeed >= 0) {
        return true;
    }
    return false;
}


train_speed_data CollisionChecker::getSpeedOfTrainClosestToFront(ITrackSegment* track) {
    train_speed_data trainSpeed = default_train_speed_data;

    if(track != NULL) {
        TrackSensor* closestRearSensor = track->getFrontSensor();
        if(closestRearSensor != NULL) {
            trainSpeed.trainPresent = closestRearSensor->isTrainPresent();
            trainSpeed.trainId = closestRearSensor->getTrainId();
            trainSpeed.trainSpeed = closestRearSensor->getTrainSpeed();
        }
    }

    return trainSpeed;
}

train_speed_data CollisionChecker::getSpeedOfTrainClosestToRear(ITrackSegment* track) {
    train_speed_data trainSpeed = default_train_speed_data;
    if(track != NULL) {
        TrackSensor* closestForwardSensor = track->getRearSensor();
        if(closestForwardSensor != NULL) {
            trainSpeed.trainPresent = closestForwardSensor->isTrainPresent();
            trainSpeed.trainId = closestForwardSensor->getTrainId();
            trainSpeed.trainSpeed = closestForwardSensor->getTrainSpeed();
        }
    }
    return trainSpeed;
}
