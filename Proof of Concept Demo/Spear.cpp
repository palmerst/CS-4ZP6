#include "Spear.h"

Spear::Spear(float x, float y) : DynamicObject(x, y, 500.0f, 50.0f, 0.05f, 1.0f, OBJ_BOULDER, "./data/obj/spear", "./data/shader/vObject.glsl", "./data/shader/fObject.glsl"){

}

Spears::Spears(float x, float y) : DynamicObject(x, y, 500.0f, 50.0f, 0.05f, 1.0f, OBJ_BOULDER, "./data/obj/spears", "./data/shader/vObject.glsl", "./data/shader/fObject.glsl"){

}

