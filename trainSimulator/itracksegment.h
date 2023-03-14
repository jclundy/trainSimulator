#ifndef ITRACKSEGMENT_H
#define ITRACKSEGMENT_H

#include <QList>

typedef enum {
    LINEAR_TRACK,
    JUCNTION_TRACK
} track_segment_type;

class ITrackSegment
{

public:
virtual ~ITrackSegment() {}
virtual unsigned int getId() = 0;
virtual track_segment_type getType() = 0;
virtual bool isJunction() = 0;
virtual bool isLinear() = 0;
virtual float getLength() = 0;
virtual float getHeading() = 0;

virtual bool isFrontTerminal() = 0;
virtual bool isRearTerminal() = 0;

virtual ITrackSegment* getSelectedForwardEnd() = 0;
virtual ITrackSegment* getSelectedRearEnd() = 0;

virtual QList<ITrackSegment*> getForwardNeighbours() = 0;
virtual QList<ITrackSegment*> getRearNeighbours() = 0;

virtual QPointF getFrontEndPosition() = 0;
virtual QPointF getRearEndPosition() = 0;
virtual QPointF getCenter() = 0;

virtual bool connectRearToTrack(ITrackSegment *track) = 0;
virtual bool connectFrontToTrack(ITrackSegment *track) = 0;

};

#endif // ITRACKSEGMENT_H
