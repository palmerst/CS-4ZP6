#include "Wall.h"

Wall::Wall(float y1, float y2, float xmid) : StaticObject(cpv(xmid-25,y1), cpv(xmid+25,y2), OBJ_BOUNDARY){

    gpuDataCount = 1;

    gpuDataList.push_back(gpuStore.add("./data/obj/testbound"));
    shaderList.push_back(shaderStore.add("./data/shader/vObject.glsl", "./data/shader/fUniversal.glsl"));

}
