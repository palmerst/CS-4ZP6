#include "PhysicsObject.h"

cpSpace* PhysicsObject::space = 0;

void PhysicsObject::render(){

    cpVect pos = cpBodyGetPosition(body);
    float angle = cpBodyGetAngle(body);

    Obj::render(glm::vec3(pos.x, pos.y, 0), angle, true);

}
