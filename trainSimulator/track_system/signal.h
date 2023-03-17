#ifndef SIGNAL_H
#define SIGNAL_H

#include "track_components/itracksegment.h"

typedef enum {
    SIGNAL_UNPLACED,
    SIGNAL_TRACK_FRONT,
    SIGNAL_TRACK_REAR
} signal_placement;

class Signal : public ISignal
{
public:
    Signal(unsigned int id);
    ~Signal();
    // ISignal Interface
    bool isRed() override;
    bool isGreen() override;
    // setters and getters
    unsigned int getId();
    void setRed();
    void setGreen();
    void setState(bool state);
    ITrackSegment* getTrackSegment();
    signal_placement getPlacement();
    // placement
    bool placeOnTrackFront(ITrackSegment*);
    bool placeOnTrackRear(ITrackSegment*);

private:
    unsigned int m_id;
    bool m_state; // true - green; red - false
    signal_placement m_placement;
    ITrackSegment* m_trackSegment;
};

#endif // SIGNAL_H
