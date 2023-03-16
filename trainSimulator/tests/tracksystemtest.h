#ifndef TRACKSYSTEMTEST_H
#define TRACKSYSTEMTEST_H

#include "track_system/tracksystem.h"

class TrackSystemTest
{
public:
    TrackSystemTest();
    void testSetup();
    void testDriving();
    void testSignals();
private:
    TrackSystem* m_trackSystem;
};

#endif // TRACKSYSTEMTEST_H
