#include "StaticObject.h"

/*** Boundary object ***/
StaticObject::StaticObject(cpVect p1, cpVect p2, bool isRamp, float thickness){

    /*** Set physics data ***/
    body = cpSpaceAddBody(space, cpBodyNewStatic());
    cpVect position = cpvlerp(p1,p2,0.50f);
    cpBodySetPosition(body, position);
    cpVect vertices[4];
    if(isRamp){
        vertices[0] = cpvsub(p1, position);
        vertices[1] = cpvsub(cpv(p2.x, p2.y-thickness), position);
        vertices[2] = cpvsub(p2, position);
        vertices[3] = cpvsub(cpv(p1.x, p1.y+thickness), position);
    } else {
        vertices[0] = cpvsub(p1, position);
        vertices[1] = cpvsub(cpv(p2.x, p1.y), position);
        vertices[2] = cpvsub(p2, position);
        vertices[3] = cpvsub(cpv(p1.x, p2.y), position);
    }
    shape = cpSpaceAddShape(space, (cpShape*) cpPolyShapeInitRaw(cpPolyShapeAlloc(), body, 4, vertices, 0.0f));

	if(isRamp)
        height = thickness;
    else
        height = p2.y - p1.y;
	width = p2.x - p1.x;

    draw = true;

    transformOverrides = false;

}
