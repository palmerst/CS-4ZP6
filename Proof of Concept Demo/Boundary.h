#ifndef BOUNDARY_H_INCLUDED
#define BOUNDARY_H_INCLUDED

#include "StaticObject.h"

enum BSurface {

    BS_SAND

};

class Boundary : public StaticObject {

    public:

        Boundary(float x1, float x2, float y, BSurface surfaceType);

};

#endif // BOUNDARY_H_INCLUDED
