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

class Connector
{

public:
    Connector(TrackSegment* parentTrackSegment);
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
    TrackSegment* parentTrackSegment;
    Fork* fork;
};

class Fork {
public:
    Fork(Connector* parent);
    Prong* getSelectedProng();
    bool setSelectedProng(unsigned int index);
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
