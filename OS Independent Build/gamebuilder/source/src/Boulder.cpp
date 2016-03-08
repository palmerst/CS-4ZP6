#include "Boulder.h"

Boulder::Boulder(float x, float y) : DynamicObject(x, y, 500.0f, 10000.0f, 0.05f, 1.0f, OBJ_BOULDER, "./data/obj/rock", "./data/shader/vObject.glsl", "./data/shader/fObject.glsl")
{

}
