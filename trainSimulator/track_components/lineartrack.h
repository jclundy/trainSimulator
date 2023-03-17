#ifndef TRACKSEGMENT_H
#define TRACKSEGMENT_H

#include "junctiontrack.h"
#include "basictracksegment.h"
#include <QLineF>

class TrainTest;

class LinearTrack : public BasicTrackSegment
{
friend class TrainTest;
public:
    LinearTrack(unsigned int id, float length = 20, const QPointF &position = QPointF(0,0));
    ~LinearTrack();

    // ITrackSegment Interface
    track_segment_type getType() override;
    bool isJunction() override;
    bool isLinear() override;

    bool isFrontTerminal() override;
    bool isRearTerminal() override;

    ITrackSegment* getSelectedForwardEnd() override;
    ITrackSegment* getSelectedRearEnd() override;
    QList<ITrackSegment*> getForwardNeighbours() override;
    QList<ITrackSegment*> getRearNeighbours() override;

    bool isConnectedForward() override;
    bool isConnectedReverse() override;

    bool connectRearToTrack(ITrackSegment *track) override;
    bool connectFrontToTrack(ITrackSegment *track) override;
    void disconnectFromTrackSegment(ITrackSegment *track) override;

    void addFrontConnection(ITrackSegment* track) override;
    void addRearConnection(ITrackSegment* track) override;

    void updateRearPosition(ITrackSegment* track) override;
    void updateFrontPosition(ITrackSegment* track) override;

    // connectors
    void disconnectBothEnds();
    void disconnectFront();
    void disconnectRear();

    bool connectRearToTrack(LinearTrack *track);
    bool connectFrontToTrack(LinearTrack *track);
    bool connectRearToTrack(JunctionTrack *track);
    bool connectFrontToTrack(JunctionTrack *track);

private:

    ITrackSegment* m_forwardTrack;
    ITrackSegment* m_rearTrack;

};

#endif // TRACKSEGMENT_H
