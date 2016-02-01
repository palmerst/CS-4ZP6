#include "StaticObject.h"

/*** Boundary object ***/
StaticObject::StaticObject(cpVect p1, cpVect p2, int type){

    /*** Set physics data ***/
    body = cpSpaceAddBody(space, cpBodyNewStatic());
    cpBodySetPosition(body, cpvlerp(p1,p2,0.50f));
    shape = cpSpaceAddShape(space, cpBoxShapeNew(body, p2.x - p1.x, p2.y - p1.y, 0.1f));
	cpShapeSetElasticity(shape, 0.5f);
	cpShapeSetFriction(shape, 1.0f);
	height = p2.y - p1.y;
	width = p2.x - p1.x;

	modelScale = glm::vec3(width, height, 500.0f);

	cpShapeSetCollisionType(shape, type);

    draw = true;

}
