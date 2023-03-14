#ifndef TRACKSEGMENT_H
#define TRACKSEGMENT_H

#include "itracksegment.h"

class TrainTest;

class LinearTrack : public ITrackSegment
{
friend class TrainTest;
public:
    LinearTrack(unsigned int id, float length = 20, const QPointF &position = QPointF(0,0));
    ~LinearTrack();

    // ITrackSegment Interface
    track_segment_type getType() override;
    bool isJunction() override;
    bool isLinear() override;
    float getLength() override;

    bool isFrontTerminal() override;
    bool isRearTerminal() override;
    float getHeading() override;

    ITrackSegment* getSelectedForwardEnd() override;
    ITrackSegment* getSelectedRearEnd() override;
    QList<ITrackSegment*> getForwardNeighbours() override;
    QList<ITrackSegment*> getRearNeighbours() override;
    QPointF getFrontEndPosition() override;
    QPointF getRearEndPosition() override;
    bool connectRearToTrack(ITrackSegment *track) override;
    bool connectFrontToTrack(ITrackSegment *track) override;

    // connectors
    void disconnectFromNeighbours();
    bool connectRearToTrack(LinearTrack *track);
    bool connectFrontToTrack(LinearTrack *track);

    //getters
    unsigned int getId();
    QPointF getCenter();

    // modifiers
    void setCenter(const QPointF &newCenter);
    void translate(const QPointF &offset);
    void setRotationAboutCenter(float degrees);
    void setRotationAboutFront(float degrees);
    void setRotationAboutRear(float degrees);

private:
    unsigned int m_id;
    ITrackSegment* m_forwardTrack;
    ITrackSegment* m_rearTrack;

    QPointF m_forwardPosition;
    QPointF m_rearPosition;
};

#endif // TRACKSEGMENT_H
