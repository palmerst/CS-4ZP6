#include "Obj.h"

/*** Boundary object ***/
Boundary::Boundary(cpSpace* space, cpVect p1, cpVect p2, ObjGPUData* gpuData){

    /*** Set physics data ***/
    body = cpSpaceAddBody(space, cpBodyNewStatic());
    cpBodySetPosition(body, cpvlerp(p1,p2,0.50f));
    shape = cpSpaceAddShape(space, cpBoxShapeNew(body, p2.x - p1.x, p2.y - p1.y, 0.1f));
	cpShapeSetElasticity(shape, 0.5f);
	cpShapeSetFriction(shape, 1.0f);
	height = p2.y - p1.y;
	width = p2.x - p1.x;

    /*** Link gpu data ***/
    this->gpuData = gpuData;

}


/*** Generic dynamic object ***/
DynamicObject::DynamicObject(){
    body = 0;
    shape = 0;
}

DynamicObject::DynamicObject(cpSpace* space, glm::vec2 pos, float mass, float scale, float elast, float fric, ObjGPUData* gpuData, bool noRotation){

    height = scale;
	width = scale*gpuData->whRatio;

    /*** Set physics data ***/
    if(noRotation)
        body = cpBodyNew(mass, INFINITY);
    else{
        body = cpBodyNew(mass, cpMomentForBox(mass, width, height));
    }
    cpSpaceAddBody(space, body);
    cpBodySetPosition(body, cpv(pos.x, pos.y));
    shape = cpSpaceAddShape(space, cpBoxShapeNew(body, width, height, 0.01));
	cpShapeSetElasticity(shape, elast);
	cpShapeSetFriction(shape, fric);

    /*** Link gpu data ***/
    this->gpuData = gpuData;
}
