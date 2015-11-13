#include "Obj.h"

/*** Boundary object ***/
Boundary::Boundary(cpSpace* space, cpVect p1, cpVect p2, ObjGPUData* gpuData){

    /*** Set physics data ***/
    body = cpSpaceAddBody(space, cpBodyNewStatic());
    cpBodySetPosition(body, cpvlerp(p1,p2,0.50f));
    shape = cpSpaceAddShape(space, cpBoxShapeNew(body, p2.x - p1.x, p2.y - p1.y, 0.1f));
	cpShapeSetElasticity(shape, 1.0f);
	cpShapeSetFriction(shape, 1.0f);
	height = p2.y - p1.y;
	width = p2.x - p1.x;

    /*** Link gpu data ***/
    this->gpuData = gpuData;

}


/*** Generic dynamic object ***/
DynamicObject::DynamicObject(cpSpace* space, glm::vec2 pos, ObjGPUData* gpuData){

    /*** Set physics data ***/
    body = cpBodyNew(100, cpMomentForBox(100.0, 10.0, 20.0));
    cpSpaceAddBody(space, body);
    cpBodySetPosition(body, cpv(pos.x, pos.y));
    shape = cpSpaceAddShape(space, cpBoxShapeNew(body, 10.0, 20.0, 0.01));
	cpShapeSetElasticity(shape, 1.0f);
	cpShapeSetFriction(shape, 1.0f);
	height = 20.0;
	width = 10.0;

    /*** Link gpu data ***/
    this->gpuData = gpuData;
}


//HeroObject::HeroObject(cpSpace* space, glm::vec2 pos, ObjGPUData* gpuData){
//
//
//
//}
