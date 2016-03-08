#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED

#include "Surface.h"

class Platform : public Surface
{

public:

    Platform(float x1, float x2, float ymid, float thickness = 50.0f);

};


#endif // PLATFORM_H_INCLUDED
