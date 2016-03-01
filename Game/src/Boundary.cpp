#include "Boundary.h"

Boundary::Boundary(float x1, float x2, float y, BSurface surfaceType) : Surface(cpv(x1, y - 50.0f), cpv(x2, y), false) {

    cpShapeSetElasticity(shape, 0.5f);
	cpShapeSetFriction(shape, 1.0f);
	modelScale = glm::vec3(width, 0.98*height, 10000.0f);

	cpShapeSetCollisionType(shape, OBJ_SURFACE);

	if(surfaceType == BS_SAND){
        gpuDataList.push_back(gpuStore.add("./data/obj/boundary_sand", 0, false));
        shaderList.push_back(shaderStore.add("./data/shader/vBoundaryXZ.glsl", "./data/shader/fBoundary.glsl"));
	}


}
