#include "Spikes.h"
#include <iostream>

Spikes::Spikes(float x, float y, float rotation) : StaticObject(x, y, 380.0f, 0.05f, 1.0f, OBJ_FATAL_HAZARD, "./data/obj/spikes", "./data/shader/vObject.glsl", "./data/shader/fObject.glsl")
{
    // width to height = 1.26114
    // width @ 380 height = 479.2

    deathNormal = cpv(0, 1);
    cpBodySetAngle(body, rotation);
}
