#ifndef SIGNAL_H
#define SIGNAL_H

#include <track_components/itracksegment.h>

typedef enum {
    SIGNAL_UNPLACED,
    SIGNAL_TRACK_FRONT,
    SIGNAL_TRACK_REAR
} signal_position;

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
    signal_position getPosition();

    void placeOnTrackSegmentFront(ITrackSegment*);
    void placeOnTrackSegmentRear(ITrackSegment*);

private:
    bool m_state; // true - green; red - false
    signal_position m_position;
    ITrackSegment* m_trackSegment;
};

#endif // SIGNAL_H
