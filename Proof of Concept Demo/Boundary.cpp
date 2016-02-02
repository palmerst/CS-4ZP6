#include "Boundary.h"

Boundary::Boundary(float x1, float x2, float y, BSurface surfaceType) : StaticObject(cpv(x1, y), cpv(x2, y), false) {

    cpShapeSetElasticity(shape, 0.5f);
	cpShapeSetFriction(shape, 1.0f);
	modelScale = glm::vec3(width, 0, 10000.0f);

	cpShapeSetCollisionType(shape, OBJ_BOUNDARY);

	if(surfaceType == BS_SAND){
        gpuDataList.push_back(gpuStore.add("./data/obj/boundary_sand", 0, false));
        shaderList.push_back(shaderStore.add("./data/shader/vBoundaryXZ.glsl", "./data/shader/fBoundary.glsl"));
	}


}
