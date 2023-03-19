#ifndef TRACKSYSTEMTEST_H
#define TRACKSYSTEMTEST_H

#include "track_system/tracksystem.h"
#include "path_planning/trackpathtable.h"

class TrackSystemTest
{
public:
    TrackSystemTest();
    void runTests();
    void testSetup();
    void testDrive1();
    void testSignals();
    void testPathPlanning();

    // utils
    void printTrackSystemInfo();
    void printAllSignalInfo();
    void printTrackPath(QList<path_step> pathList);

private:
    TrackSystem* m_trackSystem;
    void testDriving(int iterations = 100, float dt=0.5);

};

#endif // TRACKSYSTEMTEST_H
