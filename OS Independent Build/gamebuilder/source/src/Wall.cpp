#include "Wall.h"

Wall::Wall(float y1, float y2, float xmid, float thickness) : Surface(cpv(xmid-thickness/2,y1), cpv(xmid+thickness/2,y2), false, thickness)
{


    gpuDataList.push_back(gpuStore.add("./data/obj/surface_top", 0, false));
    gpuDataList.back()->texturePlane = 2;
    gpuDataList.push_back(gpuStore.add("./data/obj/surface_bot", 0, false));
    gpuDataList.back()->texturePlane = 2;
    gpuDataList.push_back(gpuStore.add("./data/obj/surface_left", 0, false));
    gpuDataList.back()->texturePlane = 1;
    gpuDataList.back()->parallax = true;
    gpuDataList.push_back(gpuStore.add("./data/obj/surface_right", 0, false));
    gpuDataList.back()->texturePlane = 1;
    gpuDataList.back()->parallax = true;
    gpuDataList.push_back(gpuStore.add("./data/obj/surface_front", 0, false));
    gpuDataList.back()->texturePlane = 0;
    gpuDataList.back()->parallax = true;
    gpuDataList.push_back(gpuStore.add("./data/obj/surface_back", 0, false));
    gpuDataList.back()->texturePlane = 0;
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

    cpShapeSetCollisionType(shape, OBJ_SURFACE);

}
