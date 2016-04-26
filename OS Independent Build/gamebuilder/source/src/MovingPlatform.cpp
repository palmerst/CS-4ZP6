#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(float w, float speed, std::vector<cpVect>& path, float thickness)
{

    this->path = path;
    this->speed = speed;


    /*** Set physics data ***/
    body = cpSpaceAddBody(space, cpBodyNewKinematic());
    cpVect vertices[4];

    vertices[0] = cpv(- w/2.0f, - thickness/2.0f);
    vertices[1] = cpv(+ w/2.0f, - thickness/2.0f);
    vertices[2] = cpv(+ w/2.0f, + thickness/2.0f);
    vertices[3] = cpv(- w/2.0f, + thickness/2.0f);

    shape = cpSpaceAddShape(space, (cpShape*) cpPolyShapeInitRaw(cpPolyShapeAlloc(), body, 4, vertices, 0.0f));

    cpBodySetPosition(body, path[0]);
    height = thickness;
    width = w;

    draw = true;

    transformOverrides = false;

    standingNormal = cpv(0, 1);

    gpuDataList.push_back(gpuStore.add("./data/obj/surface_top", 0, false));
    gpuDataList.back()->texturePlane = 5;
    gpuDataList.push_back(gpuStore.add("./data/obj/surface_bot", 0, false));
    gpuDataList.back()->texturePlane = 5;
    gpuDataList.push_back(gpuStore.add("./data/obj/surface_left", 0, false));
    gpuDataList.back()->texturePlane = 4;
    gpuDataList.back()->parallax = true;
    gpuDataList.push_back(gpuStore.add("./data/obj/surface_right", 0, false));
    gpuDataList.back()->texturePlane = 4;
    gpuDataList.back()->parallax = true;
    gpuDataList.push_back(gpuStore.add("./data/obj/surface_front", 0, false));
    gpuDataList.back()->texturePlane = 3;
    gpuDataList.back()->parallax = true;
    gpuDataList.push_back(gpuStore.add("./data/obj/surface_back", 0, false));
    gpuDataList.back()->texturePlane = 3;
    gpuDataList.back()->parallax = true;
    shaderList.push_back(shaderStore.add("./data/shader/vSurface.glsl", "./data/shader/fObject.glsl"));
    shaderList.push_back(shaderStore.add("./data/shader/vSurface.glsl", "./data/shader/fObject.glsl"));
    shaderList.push_back(shaderStore.add("./data/shader/vSurface.glsl", "./data/shader/fObject.glsl"));
    shaderList.push_back(shaderStore.add("./data/shader/vSurface.glsl", "./data/shader/fObject.glsl"));
    shaderList.push_back(shaderStore.add("./data/shader/vSurface.glsl", "./data/shader/fObject.glsl"));
    shaderList.push_back(shaderStore.add("./data/shader/vSurface.glsl", "./data/shader/fObject.glsl"));


    cpShapeSetElasticity(shape, 0.5f);
    cpShapeSetFriction(shape, 1.0f);
    modelScale = glm::vec3(width, height, 500.0f);

    cpShapeSetCollisionType(shape, OBJ_MOVINGPLAT);

    destinationNode = 0;
    dir = 1;

    cpShapeSetUserData(shape, this);

}

void MovingPlatform::update(float dt){

    cpVect pos = cpBodyGetPosition(body);
    cpVect vel = cpBodyGetVelocity(body);

    cpVect dirTo = cpvsub(path[destinationNode], pos);

    if(cpvdist(path[destinationNode], pos) < 1.0f || vel.x * dirTo.x < 0 || vel.y * dirTo.y < 0){
        cpBodySetPosition(body, path[destinationNode]);
        int currentNode = destinationNode;
        if(destinationNode == path.size() - 1)
            dir = -1;
        else if(destinationNode == 0)
            dir = 1;
        destinationNode += dir;
        cpBodySetVelocity(body, cpvmult(cpvnormalize(cpvsub(path[destinationNode], path[currentNode])), speed));
    }

}
