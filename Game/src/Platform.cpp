#include "Platform.h"

Platform::Platform(float x1, float x2, float ymid, float thickness) : Surface(cpv(x1,ymid-thickness/2), cpv(x2,ymid+thickness/2), false, thickness)
{


    gpuDataList.push_back(gpuStore.add("./data/obj/surface_top", 0, false));
    gpuDataList.back()->texturePlane = 2;
    gpuDataList.push_back(gpuStore.add("./data/obj/surface_bot", 0, false));
    gpuDataList.back()->texturePlane = 2;
    gpuDataList.push_back(gpuStore.add("./data/obj/surface_left", 0, false));
    gpuDataList.back()->texturePlane = 1;
    gpuDataList.push_back(gpuStore.add("./data/obj/surface_right", 0, false));
    gpuDataList.back()->texturePlane = 1;
    gpuDataList.push_back(gpuStore.add("./data/obj/surface_front", 0, false));
    gpuDataList.back()->texturePlane = 0;
    gpuDataList.push_back(gpuStore.add("./data/obj/surface_back", 0, false));
    gpuDataList.back()->texturePlane = 0;
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
