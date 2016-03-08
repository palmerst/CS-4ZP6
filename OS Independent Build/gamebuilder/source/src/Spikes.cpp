#include "Spikes.h"


Spikes::Spikes(float x, float y, float rotation) : StaticObject(x, y + 190.0f, 380.0f, 0.05f, 1.0f, OBJ_FATAL_HAZARD, "./data/obj/spikes", "./data/shader/vObject.glsl", "./data/shader/fObject.glsl")
{
    deathNormal = cpv(0, 1);
    cpBodySetAngle(body, rotation);
}
