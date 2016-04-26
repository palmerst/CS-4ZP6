#include "Spear.h"

Spear::Spear(float x, float y, float rotation) : KinematicObject(x, y, 500.0f, 0.05f, 1.0f, OBJ_FATAL_HAZARD, "./data/obj/spear", "./data/shader/vObject.glsl", "./data/shader/fObject.glsl")
{
    deathNormal = cpvforangle(rotation + 3.141592f/2.0f);
    cpBodySetAngle(body, rotation);
}

void Spear::update(float dt){
}
