#include "StaticObject.h"


StaticObject::StaticObject(float x, float y, float scale, float elast, float fric, int type, std::string gpuPath, std::string vPath, std::string fPath){


    gpuDataList.push_back(gpuStore.add(gpuPath, 3.1415f));
    shaderList.push_back(shaderStore.add(vPath, fPath));

    transformOverrides = false;

    height = scale;
    modelScale = glm::vec3(scale);

    width = height*gpuDataList[0]->whRatio;

    /*** Set physics data ***/
    body = cpBodyNewStatic();
    cpSpaceAddBody(space, body);
    cpBodySetPosition(body, cpv(x, y));

    ObjGPUData* gpuData = gpuDataList[0];
    int vertCount = gpuData->vList.size();
    cpVect vertices[vertCount];

    glm::vec3 pos(x, y, 0);

    for(int i = 0; i < vertCount; i++){
        glm::vec4 currentVert = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), modelScale) * gpuData->rotation * gpuData->unitScale * glm::vec4(gpuData->vList[i],0);
        vertices[i] = cpv(currentVert.x, currentVert.y);
    }

    shape = cpSpaceAddShape(space, (cpShape*) cpPolyShapeInitRaw(cpPolyShapeAlloc(), body, vertCount, vertices, 1.0f));
	cpShapeSetElasticity(shape, elast);
	cpShapeSetFriction(shape, fric);
	cpShapeSetUserData(shape, this);
    cpShapeSetCollisionType(shape, type);

    draw = true;
}
