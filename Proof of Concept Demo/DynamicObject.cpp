#include "DynamicObject.h"

/*** Generic dynamic object ***/
DynamicObject::DynamicObject(){
    body = 0;
    shape = 0;
}


DynamicObject::DynamicObject(glm::vec2 pos, float mass, float scale, float elast, float fric, int type, std::string gpuPath, std::string vPath, std::string fPath, bool noRotation){

    gpuDataCount = 1;

    gpuDataList.push_back(gpuStore.add(gpuPath, 3.1415f));
    shaderList.push_back(shaderStore.add(vPath, fPath));

    height = scale;
    modelScale = glm::vec3(scale);

    width = height*gpuDataList[0]->whRatio;

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
	cpShapeSetUserData(shape, this);
    cpShapeSetCollisionType(shape, type);

    draw = true;
}
