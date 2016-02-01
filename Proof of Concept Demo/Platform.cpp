#include "Platform.h"

Platform::Platform(float x1, float x2, float ymid) : StaticObject(cpv(x1,ymid-25), cpv(x2,ymid+25), OBJ_BOUNDARY){

    gpuDataCount = 1;

    gpuDataList.push_back(gpuStore.add("./data/obj/testbound"));
    shaderList.push_back(shaderStore.add("./data/shader/vObject.glsl", "./data/shader/fUniversal.glsl"));

}
