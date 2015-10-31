#include "Obj.h"

Boundary::Boundary(cpSpace* space, vertexList& staticMasterVertexBuffer, cpVect p1, cpVect p2){

    /*** Set physics data ***/
    body = cpSpaceAddBody(space, cpBodyNewStatic());
    cpBodySetPosition(body, cpvlerp(p1,p2,0.50f));
    shape = cpSpaceAddShape(space, cpBoxShapeNew(body, p2.x - p1.x, p2.y - p1.y, 0.1f));
	cpShapeSetElasticity(shape, 0.5f);
	cpShapeSetFriction(shape, 1.0f);

    /*** Store geometry data ***/
    bufferLocation.first = staticMasterVertexBuffer.size();
    bufferLocation.len = 6;

    staticMasterVertexBuffer.push_back(glm::vec3(p1.x, p1.y, 0));
    staticMasterVertexBuffer.push_back(glm::vec3(p2.x, p1.y, 0));
    staticMasterVertexBuffer.push_back(glm::vec3(p1.x, p2.y, 0));
    staticMasterVertexBuffer.push_back(glm::vec3(p1.x, p2.y, 0));
    staticMasterVertexBuffer.push_back(glm::vec3(p2.x, p1.y, 0));
    staticMasterVertexBuffer.push_back(glm::vec3(p2.x, p2.y, 0));

}


Character::Character(cpSpace* space, glm::vec2 pos){

    /*** Set physics data ***/
    body = cpBodyNew(100, cpMomentForBox(100, 10, 20));
    cpSpaceAddBody(space, body);
    cpBodySetPosition(body, cpv(pos.x, pos.y));
    shape = cpSpaceAddShape(space, cpBoxShapeNew(body, 9.8, 19.8, 0.01));
	cpShapeSetElasticity(shape, 0.5f);
	cpShapeSetFriction(shape, 1.0f);

}
