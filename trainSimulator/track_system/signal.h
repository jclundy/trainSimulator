#ifndef SIGNAL_H
#define SIGNAL_H

#include <track_components/itracksegment.h>

typedef enum {
    SIGNAL_UNPLACED,
    SIGNAL_TRACK_FRONT,
    SIGNAL_TRACK_REAR
} signal_placement;

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
    signal_placement getPlacement();

    void placeOnTrackFront(ITrackSegment*);
    void placeOnTrackRear(ITrackSegment*);

private:
    bool m_state; // true - green; red - false
    signal_placement m_placement;
    ITrackSegment* m_trackSegment;
};

#endif // SIGNAL_H
