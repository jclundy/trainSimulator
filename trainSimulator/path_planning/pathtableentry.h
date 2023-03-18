#ifndef PATHTABLEENTRY_H
#define PATHTABLEENTRY_H


class PathTableEntry
{
public:
    PathTableEntry(unsigned int id, float trackLength);
    void update(unsigned int neighbourId, float neighbourDistance);

    bool getVisited();
    bool setVisited();

    unsigned int getTrackId();
    float getTrackLength();
    float getDistanceToTarget();
    float getNextId();
    int getDirectionToNext();

private:
    unsigned int m_trackId;
    float m_trackLength;
    float m_distanceToTarget;

    unsigned int m_nextId;
    int m_directionToNext; //-1=reverse, 1=forward, 0=stop

    bool m_visited;
};

#endif // PATHTABLEENTRY_H
