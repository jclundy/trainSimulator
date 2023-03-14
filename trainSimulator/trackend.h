#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QPointF>
#include <QList>

class LinearTrack;
class TrainTest;

typedef enum {
    TRACK_FRONT,
    TRACK_REAR
} track_pole;

class TrackEnd {
friend class TrainTest;

public:
    TrackEnd(LinearTrack* parent, track_pole pole);

    // Public Methods
    bool isFront();
    bool isRear();

    bool isTerminal();
    bool isFork();

    bool connectTo(TrackEnd* neighbour);

    // disconnectors
    void disconnect(TrackEnd* neighbour);
    void disconnectAll();
    void validateSelectedForkNumber();

    // Queries
    LinearTrack* getParentTrackSegment();
    LinearTrack* getSelectedTrackSegment();
    TrackEnd* getSelectedTrackEnd();
    int getSelectedForkNumber();
    bool isNeighbour(TrackEnd* connector, int &forkNumber);
    int getMyForkNumberForNeighbour(TrackEnd* neighbour);
    int getNeighboursForkNumberForMe(TrackEnd* neighbour);
    bool isConnectedToNeighbourBothWays();

    // Fork-related methods
    bool setSelectedFork(int index);
    void toggleSelectedFork();

    // public members
    QPointF m_position;

    // neighbours need to access:
    QList<TrackEnd*> m_neighbourList;

private:
    // private methods
    track_pole m_pole;
    static int maxForks() {return 2;}

    // private members
    int m_selectedIndex;
    LinearTrack* m_parentTrackSegment;
};

#endif // CONNECTOR_H
