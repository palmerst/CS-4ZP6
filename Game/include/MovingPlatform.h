#ifndef MOVINGPLATFORM_H_INCLUDED
#define MOVINGPLATFORM_H_INCLUDED

#include "KinematicObject.h"
#include <vector>

class MovingPlatform : public KinematicObject
{
    int dir;
    float speed;
    int destinationNode;
    std::vector<cpVect> path;

    public:
    MovingPlatform(float w, float speed, std::vector<cpVect>& path, float thickness = 50.0f);
    void update(float dt);

};

#endif // MOVINGPLATFORM_H_INCLUDED
