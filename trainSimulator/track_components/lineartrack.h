#ifndef TRACKSEGMENT_H
#define TRACKSEGMENT_H

#include "itracksegment.h"
#include "junctiontrack.h"
#include <QLineF>

class TrainTest;

class LinearTrack : public ITrackSegment
{
friend class TrainTest;
public:
    LinearTrack(unsigned int id, float length = 20, const QPointF &position = QPointF(0,0));
    ~LinearTrack();

    // ITrackSegment Interface
    unsigned int getId() override;
    TrackGeometry* getTrackGeometry() override;
    float getLength() override;

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

    ISignal* getFrontSignal() override;
    ISignal* getRearSignal() override;
    bool placeFrontSignal(ISignal* signal) override;
    bool placeRearSignal(ISignal* signal) override;

    // connectors
    void disconnectBothEnds();
    void disconnectFront();
    void disconnectRear();

    bool connectRearToTrack(LinearTrack *track);
    bool connectFrontToTrack(LinearTrack *track);
    bool connectRearToTrack(JunctionTrack *track);
    bool connectFrontToTrack(JunctionTrack *track);

private:
    unsigned int m_id;
    ITrackSegment* m_forwardTrack;
    ITrackSegment* m_rearTrack;
    TrackGeometry m_trackGeometry;
    ISignal * m_frontSignal;
    ISignal * m_rearSignal;
};

#endif // TRACKSEGMENT_H
