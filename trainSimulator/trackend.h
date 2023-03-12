#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QPointF>
#include <QList>

class TrackSegment;

typedef enum {
    TRACK_FRONT,
    TRACK_REAR
} track_pole;

class TrackEnd {
public:
    TrackEnd(TrackSegment* parent, track_pole pole);

    // Public Methods
    bool isFront();
    bool isRear();

    bool isTerminal();
    bool isFork();

    bool connectTo(TrackEnd* neighbour);

    // Search methods
    TrackSegment* getSelectedTrackSegment();
    TrackEnd* getSelectedTrackEnd();
    bool isNeighbour(TrackEnd* connector, int &forkNumber);
    int getMyForkNumberForNeighbour(TrackEnd* neighbour);
    int getNeighboursForkNumberForMe(TrackEnd* neighbour);

    // Fork-related methods
    bool setSelectedFork(int index);
    void toggleSelectedFork();

    // public members
    QPointF m_position;

    // neighbours need to access:
    QList<TrackEnd*> m_neighbourList;
    TrackSegment* m_parentTrackSegment;

private:
    // private methods
    track_pole m_pole;
    static int maxForks() {return 2;}

    // private members
    unsigned int m_selectedIndex;

};

#endif // CONNECTOR_H
