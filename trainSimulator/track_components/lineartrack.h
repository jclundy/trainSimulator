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

    bool connectRearToTrack(ITrackSegment *track) override;
    bool connectFrontToTrack(ITrackSegment *track) override;
    void disconnectFromTrackSegment(ITrackSegment *track) override;

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

    void updateRearPosition(ITrackSegment* track);
    void updateFrontPosition(ITrackSegment* track);
};

#endif // TRACKSEGMENT_H
