#include "Hero.h"

Hero::Hero(float x, float y) : DynamicObject(200, "./data/obj/testchar", "./data/shader/vObject.glsl", "./data/shader/fObject.glsl") {

    float mass = 100.0f;

    body = cpBodyNew(mass, INFINITY);
    cpSpaceAddBody(space, body);
    cpBodySetPosition(body, cpv(x, y));
    shape = cpSpaceAddShape(space, cpBoxShapeNew(body, width, height, 0.01));
	cpShapeSetElasticity(shape, 0);
	cpShapeSetFriction(shape, 0);
	cpShapeSetUserData(shape, this);
    cpShapeSetCollisionType(shape, OBJ_HERO);

}
