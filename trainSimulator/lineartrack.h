#ifndef TRACKSEGMENT_H
#define TRACKSEGMENT_H

#include "trackend.h"
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
    TrackEnd* getSelectedForwardEnd() override;
    TrackEnd* getSelectedRearEnd() override;
    QList<ITrackSegment> getForwardNeighbours() override;
    QList<ITrackSegment> getRearNeighbours() override;
    QPointF getFrontEndPosition() override;
    QPointF getRearEndPosition() override;
    bool connectRearToTrack(ITrackSegment *track) override;
    bool connectFrontToTrack(ITrackSegment *track) override;

    // public methods
    void disconnectFromNeighbours();
    bool connectRearToTrack(LinearTrack *track);
    bool connectFrontToTrack(LinearTrack *track);

    //getters
    unsigned int getId();
    TrackEnd* getForwardEnd();
    TrackEnd* getRearEnd();
    QPointF getCenter();
    float getHeading();

    // modifiers
    void setCenter(const QPointF &newCenter);
    void translate(const QPointF &offset);
    void setRotationAboutCenter(float degrees);
    void setRotationAboutFront(float degrees);
    void setRotationAboutRear(float degrees);

private:
    unsigned int m_id;
    TrackEnd m_forwardEnd;
    TrackEnd m_rearEnd;
};

#endif // TRACKSEGMENT_H
