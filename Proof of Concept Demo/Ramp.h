#ifndef RAMP_H_INCLUDED
#define RAMP_H_INCLUDED

#include "StaticObject.h"

class Ramp : public StaticObject {

    public:

        Ramp(float x1, float x2, float y1, float y2, float thickness = 50.0f);

};

#endif // RAMP_H_INCLUDED
