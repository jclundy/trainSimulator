#include "collisionchecker.h"

bool CollisionChecker::collisionWillOccur(ITrackSegment* rearTrack, ITrackSegment* frontTrack) {

    train_speed_data rearTrain = getRearTrackTrainSpeed(rearTrack);
    train_speed_data frontTrain = getFrontTrackTrainSpeed(frontTrack);

    if(rearTrain.trainPresent && frontTrain.trainPresent && rearTrain.trainId != frontTrain.trainId) {
        return rearTrain.trainSpeed> frontTrain.trainSpeed;
    }
    return false;
}

bool CollisionChecker::collisionWillOccurInForwardDirection(ITrackSegment* rearTrack, ITrackSegment* frontTrack) {
    return false;
}

bool CollisionChecker::collisionWillOccurInReverseDirection(ITrackSegment* rearTrack, ITrackSegment* frontTrack) {
    return false;
}

bool CollisionChecker::trainBlockingForward(ITrackSegment* currentTrack) {
    ITrackSegment* frontTrack = currentTrack->getSelectedForwardEnd();
    train_speed_data frontTrain = getFrontTrackTrainSpeed(frontTrack);

    if(frontTrain.trainPresent && frontTrain.trainSpeed <= 0) {
        return true;
    }
    return false;
}

bool CollisionChecker::trainBlockingRear(ITrackSegment* currentTrack) {
    ITrackSegment* rearTrack = currentTrack->getSelectedRearEnd();
    train_speed_data rearTrain = getRearTrackTrainSpeed(rearTrack);

    if(rearTrain.trainPresent && rearTrain.trainSpeed >= 0) {
        return true;
    }
    return false;
}


// should be named get train speed of train closest to rear
train_speed_data CollisionChecker::getRearTrackTrainSpeed(ITrackSegment* rearTrack) {
    train_speed_data trainSpeed = default_train_speed_data;

    if(rearTrack != NULL) {
        TrackSensor* closestRearSensor = rearTrack->getFrontSensor();
        if(closestRearSensor != NULL) {
            trainSpeed.trainPresent = closestRearSensor->isTrainPresent();
            trainSpeed.trainId = closestRearSensor->getTrainId();
            trainSpeed.trainSpeed = closestRearSensor->getTrainSpeed();
        }
    }

    return trainSpeed;
}

// should be named get train speed of train closest to front
train_speed_data CollisionChecker::getFrontTrackTrainSpeed(ITrackSegment* frontTrack) {
    train_speed_data trainSpeed = default_train_speed_data;
    if(frontTrack != NULL) {
        TrackSensor* closestForwardSensor = frontTrack->getRearSensor();
        if(closestForwardSensor != NULL) {
            trainSpeed.trainPresent = closestForwardSensor->isTrainPresent();
            trainSpeed.trainId = closestForwardSensor->getTrainId();
            trainSpeed.trainSpeed = closestForwardSensor->getTrainSpeed();
        }
    }
    return trainSpeed;
}
