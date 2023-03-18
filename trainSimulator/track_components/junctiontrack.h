#ifndef JUNCTIONTRACK_H
#define JUNCTIONTRACK_H

#include "basictracksegment.h"
#include "junction.h"

class JunctionTrack : public BasicTrackSegment
{
friend class TrainTest;

public:
    JunctionTrack(unsigned int id, float length = 20, const QPointF &position = QPointF(0,0), unsigned int maxBranches = 2);
    ~JunctionTrack();

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
    Junction m_forwardJunction;
    Junction m_rearJunction;
};

#endif // JUNCTIONTRACK_H
