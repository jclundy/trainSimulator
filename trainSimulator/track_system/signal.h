#ifndef SIGNAL_H
#define SIGNAL_H

#include <track_components/itracksegment.h>

class Signal
{
public:
    Signal();
    bool isRed();
    bool isGreen();
    void setRed();
    void setGreen();
    void setState(bool state);
    ITrackSegment* getTrackSegment();

    void placeOnTrackSegmentFront(ITrackSegment*);
    void placeOnTrackSegmentRear(ITrackSegment*);

private:
    bool m_state; // true - green; red - false
    ITrackSegment* m_trackSegment;
};

#endif // SIGNAL_H
