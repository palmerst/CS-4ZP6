#include "Goal.h"

Goal::Goal(float x1, float x2, float ymid, float thickness) : Surface(cpv(x1,ymid-thickness/2), cpv(x2,ymid+thickness/2), false, thickness)
{


    gpuDataList.push_back(gpuStore.add("./data/obj/goal_top", 0, false));
    gpuDataList.back()->texturePlane = 2;
    gpuDataList.push_back(gpuStore.add("./data/obj/goal_bot", 0, false));
    gpuDataList.back()->texturePlane = 2;
    gpuDataList.push_back(gpuStore.add("./data/obj/goal_left", 0, false));
    gpuDataList.back()->texturePlane = 1;
    gpuDataList.back()->parallax = true;
    gpuDataList.push_back(gpuStore.add("./data/obj/goal_right", 0, false));
    gpuDataList.back()->texturePlane = 1;
    gpuDataList.back()->parallax = true;
    gpuDataList.push_back(gpuStore.add("./data/obj/goal_front", 0, false));
    gpuDataList.back()->texturePlane = 0;
    gpuDataList.back()->parallax = true;
    gpuDataList.push_back(gpuStore.add("./data/obj/goal_back", 0, false));
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

    cpShapeSetCollisionType(shape, OBJ_GOAL);
}
