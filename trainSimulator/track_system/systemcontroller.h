#ifndef SYSTEMCONTROLLER_H
#define SYSTEMCONTROLLER_H

#include "train/train.h"
#include "path_planning/trackpathtable.h"
#include "track_components/junction.h"
#include "track_system/tracksystem.h"

#include <QMap>

class SystemController
{
public:
    SystemController(TrackSystem* system);
    ~SystemController();

    void setAllTrainDestinations(QMap<unsigned int, unsigned int>); // key - trainId, value - trackId
    void setTrainDestination(int trainId, int destinationId);
    void controlTrains();
    void controlJunctions();

private:
    TrackSystem* m_trackSystem;
    QMap<unsigned int, TrackPathTable*> m_trainPaths;
};

#endif // SYSTEMCONTROLLER_H
