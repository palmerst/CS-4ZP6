#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED

#include "StaticObject.h"

class Platform : public StaticObject {

    public:

        Platform(float x1, float x2, float ymid, float thickness = 50.0f);

};


#endif // PLATFORM_H_INCLUDED
