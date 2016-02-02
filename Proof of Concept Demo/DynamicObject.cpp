#include "DynamicObject.h"

/*** Generic dynamic object ***/
DynamicObject::DynamicObject(){
    body = 0;
    shape = 0;
}


DynamicObject::DynamicObject(float scale, std::string gpuPath, std::string vPath, std::string fPath){


    gpuDataList.push_back(gpuStore.add(gpuPath, 3.1415f));
    shaderList.push_back(shaderStore.add(vPath, fPath));

    transformOverrides = false;

    height = scale;
    modelScale = glm::vec3(scale);

    width = height*gpuDataList[0]->whRatio;

    /*** Set physics data ***/


    draw = true;
}
