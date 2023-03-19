#ifndef PATHTABLEENTRY_H
#define PATHTABLEENTRY_H

typedef enum {
    PATH_REVERSE_DIRECTION = -1,
    PATH_STAY_PUT = 0,
    PATH_FORWARD_DIRECTION = 1,
} path_direction;

class PathTableEntry
{
public:
    PathTableEntry() {}
    PathTableEntry(unsigned int id, float trackLength);
    void initializeAsTarget();
    void update(unsigned int neighbourId, float neighbourDistance, path_direction direction);

    bool getVisited();
    void setVisited();

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
