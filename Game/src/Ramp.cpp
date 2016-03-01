#include "Ramp.h"

Ramp::Ramp(float x1, float x2, float y1mid, float y2mid, float thickness) : Surface(cpv(x1,y1mid-thickness/2), cpv(x2,y2mid+thickness/2), true, thickness){


    gpuDataList.push_back(gpuStore.add("./data/obj/surface_top", 0, false));
    gpuDataList.push_back(gpuStore.add("./data/obj/surface_bot", 0, false));
    gpuDataList.push_back(gpuStore.add("./data/obj/surface_left", 0, false));
    gpuDataList.push_back(gpuStore.add("./data/obj/surface_right", 0, false));
    gpuDataList.push_back(gpuStore.add("./data/obj/surface_front", 0, false));
    gpuDataList.push_back(gpuStore.add("./data/obj/surface_back", 0, false));
    shaderList.push_back(shaderStore.add("./data/shader/vSurfaceXZ.glsl", "./data/shader/fObject.glsl"));
    shaderList.push_back(shaderStore.add("./data/shader/vSurfaceXZ.glsl", "./data/shader/fObject.glsl"));
    shaderList.push_back(shaderStore.add("./data/shader/vSurfaceYZ.glsl", "./data/shader/fObject.glsl"));
    shaderList.push_back(shaderStore.add("./data/shader/vSurfaceYZ.glsl", "./data/shader/fObject.glsl"));
    shaderList.push_back(shaderStore.add("./data/shader/vSurfaceXY.glsl", "./data/shader/fObject.glsl"));
    shaderList.push_back(shaderStore.add("./data/shader/vSurfaceXY.glsl", "./data/shader/fObject.glsl"));

    transformOverrides = true;

    float dy = (y2mid - y1mid)/2.0;
    float dx = (x2 - x1)/2.0;

    translationOverrideList.push_back(glm::vec3());
    translationOverrideList.push_back(glm::vec3());
    translationOverrideList.push_back(glm::vec3(0, -dy, 0));
    translationOverrideList.push_back(glm::vec3(0, dy, 0));
    translationOverrideList.push_back(glm::vec3());
    translationOverrideList.push_back(glm::vec3());

    float angle = atan2(dy, dx);

    rotationOverrideList.push_back(0);
    rotationOverrideList.push_back(0);
    rotationOverrideList.push_back(0);
    rotationOverrideList.push_back(0);
    rotationOverrideList.push_back(0);
    rotationOverrideList.push_back(0);

    glm::mat4 shear = glm::shearY3D(glm::mat4(1.0f), dy/dx, 0.0f);

    shearOverrideList.push_back(shear);
    shearOverrideList.push_back(shear);
    shearOverrideList.push_back(glm::mat4(1.0f));
    shearOverrideList.push_back(glm::mat4(1.0f));
    shearOverrideList.push_back(shear);
    shearOverrideList.push_back(shear);


    cpShapeSetElasticity(shape, 0.5f);
	cpShapeSetFriction(shape, 1.0f);
	modelScale = glm::vec3(width, height, 500.0f);

	cpShapeSetCollisionType(shape, OBJ_SURFACE);

	standingNormal = cpvperp(cpv(dx,dy));
}
