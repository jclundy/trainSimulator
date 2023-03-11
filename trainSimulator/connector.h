#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QPointF>
#include <QList>

class Connector;
class Fork;
class Prong;
class TrackSegment;

typedef enum {
    TERMINAL,
    LINEAR,
    FORK
} connector_type;

typedef enum {
    TRACK_FRONT,
    TRACK_REAR
} track_end;

class Connector
{

public:
    Connector(TrackSegment* m_parentTrackSegment, track_end trackEnd);
    ~Connector();
    // public methods
    connector_type getConnectionType();
    bool isFront();
    bool isRear();

    bool isTerminal();
    bool isFork();

    // modifiers
    bool connectTo(Connector* neighbour);

    // search methods
    TrackSegment* getTrackSegment();
    TrackSegment* getConnectedTrackSegment();
    Connector* getNeighbouringConnection();



    // public members
    QPointF m_position;

private:
    // private methods

    // private members
    connector_type m_connectionType;
    track_end m_trackEnd;
    TrackSegment* m_parentTrackSegment;
    Fork* m_fork;
};

class Fork {
public:
    Fork(Connector* parent);
    Prong* getSelectedProng();
    bool setSelectedProng(int index);
    void toggleSelectedProng();
    int findIndexOfProngConnectedToNeighbour(Connector* neighbour);

    Connector* m_parentConnector;

private:
    // private methods
    void addProng(float angle = 0, float length = 1);

    // private members
    unsigned int m_selectedIndex;
    QList<Prong*> m_prongList;

};

class Prong {
public:
    Prong(Fork* parent, uint8_t idx, float angle = 0, float length = 1);
    bool isNeighbourConnected();
    void connect(Prong* neighbour);

    bool isNeighbour(Connector* connector);

    Fork* m_parentFork;
    Prong* m_neighbour;
private:
    // private members

    // geometry
    float m_angle; // relative to track segment
    float m_length;
    uint8_t m_index;
};

#endif // CONNECTOR_H
