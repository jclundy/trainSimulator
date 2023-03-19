#ifndef SYSTEMCONTROLLER_H
#define SYSTEMCONTROLLER_H

#include "train/train.h"
#include "path_planning/trackpathtable.h"
#include "track_components/junction.h"
#include "track_system/tracksystem.h"

#include <QMap>

typedef struct {
    float speed;
    float dt;
    float distance;
    int trainId;
} train_approach_data;

class SystemController
{
public:
    SystemController(TrackSystem* system);
    ~SystemController();

    void setAllTrainDestinations(QMap<unsigned int, unsigned int> trainDestinations); // key - trainId, value - trackId
    void setTrainDestination(int trainId, int destinationId);
    void controlTrains();
    void controlJunctions(); // todo - rename to controlJunctionTracks

    void stopAllTrains();

    QMap<unsigned int, TrackPathTable*> getTrainPaths();

private:
    TrackSystem* m_trackSystem;
    QMap<unsigned int, TrackPathTable*> m_trainPaths;

    // Junction control methods
    void controlSingleJunction(JunctionTrack* track);  // todo - rename to controlSingleJunctionTrack
    void handleTrainOnJunctionTrack(JunctionTrack* track, int trainID);
    void handleApproachingTrains(JunctionTrack* track);
    int getIdOfClosestApproachingTrain(JunctionTrack* track);
    train_approach_data computeTrainApproachData(TrackSensor* sensor);
    train_approach_data getCloserTrain(train_approach_data winner, train_approach_data candidate);
};

#endif // SYSTEMCONTROLLER_H
