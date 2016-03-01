#include "Spear.h"

Spear::Spear(float x, float y) : DynamicObject(x, y, 500.0f, 50.0f, 0.05f, 1.0f, OBJ_FATAL_HAZARD, "./data/obj/spear", "./data/shader/vObject.glsl", "./data/shader/fObject.glsl"){
    deathNormal = cpvzero;
}

Spears::Spears(float x, float y) : StaticObject(x, y + 250.0, 500.0f, 0.05f, 1.0f, OBJ_FATAL_HAZARD, "./data/obj/spears", "./data/shader/vObject.glsl", "./data/shader/fObject.glsl"){
    deathNormal = cpv(0, 1);
}

