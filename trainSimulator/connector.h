#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QPointF>

class Connector;
class Fork;
class Prong;
class TrackSegment;

typedef enum {
    TERMINAL,
    LINEAR,
    FORK
} connector_type;

class Connector
{

public:
    Connector(TrackSegment* parent);
    ~Connector();

    // public methods
    connector_type getConnectionType();
    bool isFront();
    bool isRear();
    TrackSegment* getTrackSegment();

    // public members
    QPointF position;

    TrackSegment* getConnectedTrackSegment();
    Connector* getNeighbouringConnection();

private:
    // private methods

    // private members
    connector_type connectionType;
    bool m_isFront;
    TrackSegment* parent;
    Fork* fork;
};

class Fork {
public:
    Fork(Connector* parent);
    QList<Prong*> prongList;
    Prong* getSelectedProng();
private:
    unsigned int maxProngs; // for now keep to 2
    unsigned int selectedIndex;
    Connector* parent;
} Fork;

class Prong {
public:
    Prong(Fork* parent);
    bool isNeighbourConnected();
private:
    // private members
    Fork* parent;
    Prong * neighbour;

    // geometry
    float angle; // relative to track segment
    float length;
};

#endif // CONNECTOR_H
