#include "Boulder.h"

Boulder::Boulder(float x, float y) : DynamicObject(500.0f, "./data/obj/rock", "./data/shader/vObject.glsl", "./data/shader/fObject.glsl"){

    float rAve = (width + height)/4.0f;
    float mass = 10000;

    body = cpBodyNew(mass, cpMomentForCircle(mass, 0, rAve, cpvzero));
    cpSpaceAddBody(space, body);
    cpBodySetPosition(body, cpv(x, y));
    shape = cpSpaceAddShape(space, cpCircleShapeNew(body, rAve, cpvzero));
	cpShapeSetElasticity(shape, 0.05f);
	cpShapeSetFriction(shape, 0.9f);
	cpShapeSetUserData(shape, this);
    cpShapeSetCollisionType(shape, OBJ_BOULDER);

}
