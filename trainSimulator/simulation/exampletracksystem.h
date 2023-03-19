#ifndef EXAMPLETRACKSYSTEM_H
#define EXAMPLETRACKSYSTEM_H

#include "track_system/tracksystem.h"

class ExampleTrackSystem
{
public:
    static TrackSystem * generateExample1();
    static QMap<unsigned int, unsigned int> generateExample1Destinations();
};

#endif // EXAMPLETRACKSYSTEM_H
