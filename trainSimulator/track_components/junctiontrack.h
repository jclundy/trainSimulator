#ifndef JUNCTIONTRACK_H
#define JUNCTIONTRACK_H

#include "itracksegment.h"
#include "junction.h"

class JunctionTrack : public ITrackSegment
{
friend class TrainTest;

public:
    JunctionTrack(unsigned int id, float length = 20, const QPointF &position = QPointF(0,0), unsigned int maxBranches = 2);
    ~JunctionTrack();

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
    void disconnectFromNeighbours();
    void disconnectFront();
    void disconnectRear();

private:
    // private members
    unsigned int m_id;
    Junction m_forwardJunction;
    Junction m_rearJunction;

    TrackGeometry m_trackGeometry;
};

#endif // JUNCTIONTRACK_H
