#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QPointF>
#include <QList>

class Prong;
class TrackSegment;

typedef enum {
    TRACK_FRONT,
    TRACK_REAR
} track_pole;

class TrackEnd {
public:
    TrackEnd(TrackSegment* m_parentTrackSegment, track_pole pole);

    // Public Methods
    bool isFront();
    bool isRear();

    bool isTerminal();
    bool isFork();

    bool connectTo(TrackEnd* neighbour);

    // Search methods
    TrackSegment* getSelectedTrackSegment();
    TrackEnd* getSelectedTrackEnd();

    // Fork-related methods
    Prong* getSelectedProng();
    bool setSelectedProng(int index);
    void toggleSelectedProng();
    int findIndexOfProngConnectedToNeighbour(TrackSegment* neighbour);

    // public members
    QPointF m_position;

private:
    // private methods
    void addProng(float angle = 0, float length = 1);
    track_pole m_trackEnd;

    // private members
    TrackSegment* m_parentTrackSegment;
    unsigned int m_selectedIndex;
    QList<Prong*> m_prongList;
    QList<TrackEnd*> m_neighbourList;
};

class Prong {
public:
    Prong(TrackEnd* parent, uint8_t idx, float angle = 0, float length = 1);
    bool isNeighbourConnected();
    void connect(Prong* neighbour);

    bool isNeighbour(TrackEnd* connector);

    TrackEnd* m_parentFork;
    Prong* m_neighbour;
private:
    // private members

    // geometry
    float m_angle; // relative to track segment
    float m_length;
    uint8_t m_index;
};

#endif // CONNECTOR_H
