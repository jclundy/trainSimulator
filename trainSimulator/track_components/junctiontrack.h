#ifndef JUNCTIONTRACK_H
#define JUNCTIONTRACK_H

#include "itracksegment.h"

class JunctionTrack : public ITrackSegment
{
friend class TrainTest;

public:
    JunctionTrack(unsigned int id, float length = 20, const QPointF &position = QPointF(0,0), unsigned int maxBranches = 2);
    ~JunctionTrack();

    // ITrackSegment Interface
    track_segment_type getType() override;
    bool isJunction() override;
    bool isLinear() override;
    float getLength() override;
    ITrackSegment* getSelectedForwardEnd() override;
    ITrackSegment* getSelectedRearEnd() override;
    QList<ITrackSegment*> getForwardNeighbours() override;
    QList<ITrackSegment*> getRearNeighbours() override;
    QPointF getFrontEndPosition() override;
    QPointF getRearEndPosition() override;
    bool connectRearToTrack(ITrackSegment *track) override;
    bool connectFrontToTrack(ITrackSegment *track) override;
    void disconnectFromTrackSegment(ITrackSegment *track) override;


    // connectors
    void disconnectFromNeighbours();
    void disconnectFront();
    void disconnectRear();

    bool connectTrackToFront(ITrackSegment *track);
    bool connectTrackToRear(ITrackSegment *track);

    //getters
    unsigned int getId();
    QPointF getCenter();
    float getHeading();

private:
    // private members
    unsigned int m_id;
    QList<ITrackSegment*> m_forwardConnections;
    QList<ITrackSegment*> m_rearConnections;

    unsigned int m_selectedForwardIndex;
    unsigned int m_selectedRearIndex;

    QPointF m_center;
    float m_length;
    float m_heading;

    // private methods
    void validateSelectedForwardIndex();
    void validateSelectedRearIndex();
};

#endif // JUNCTIONTRACK_H
