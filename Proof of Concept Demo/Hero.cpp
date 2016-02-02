#include "Hero.h"

Hero::Hero(float x, float y) : DynamicObject(x, y, 200.0f, 100.0f, 0.0f, 0.0f, OBJ_HERO, "./data/obj/testchar", "./data/shader/vObject.glsl", "./data/shader/fObject.glsl") {

    cpBodySetMoment(body, INFINITY);
    startPos = cpv(x, y);

}
