#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

#include "StaticObject.h"

class Wall : public StaticObject {

    public:

        Wall(float y1, float y2, float xmid, float thickness = 50.0f);

};

#endif // WALL_H_INCLUDED
