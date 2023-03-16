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

    void addFrontConnection(ITrackSegment* track) override;
    void addRearConnection(ITrackSegment* track) override;

    void updateRearPosition(ITrackSegment* track) override;
    void updateFrontPosition(ITrackSegment* track) override;

    ISignal* getFrontSignal() override;
    ISignal* getRearSignal() override;
    bool placeFrontSignal(ISignal* signal) override;
    bool placeRearSignal(ISignal* signal) override;

    // connectors
    void disconnectFromNeighbours();
    void disconnectFront();
    void disconnectRear();

    // switch
    bool selectForwardBranch(ITrackSegment* track);
    bool selectForwardBranchById(unsigned int id);
    bool selectRearBranch(ITrackSegment* track);
    bool selectRearBranchById(unsigned int id);


private:
    // private members
    unsigned int m_id;
    Junction m_forwardJunction;
    Junction m_rearJunction;

    TrackGeometry m_trackGeometry;
    ISignal * m_frontSignal;
    ISignal * m_rearSignal;
};

#endif // JUNCTIONTRACK_H
