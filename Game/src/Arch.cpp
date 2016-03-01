#include "Arch.h"

Arch::Arch(float x, float y, bool faceRight){

    angle = 0;

    draw = true;

    gpuDataList.push_back(gpuStore.add("./data/obj/door"));
    shaderList.push_back(shaderStore.add("./data/shader/vObject.glsl", "./data/shader/fObject.glsl"));

    width = 500.0f;
    height = width/gpuDataList.back()->whRatio;

    modelScale = glm::vec3(height);

    position = glm::vec3(x, y + height/2.0f, 0);

    transformOverrides = true;
    translationOverrideList.push_back(glm::vec3());
    rotationOverrideList.push_back(0.0f);

    if(faceRight){
        shearOverrideList.push_back(glm::rotate(glm::mat4(1.0f), 3.141592f*1.0f/2.0f, glm::vec3(0, 1,0)));
    } else {
        shearOverrideList.push_back(glm::rotate(glm::mat4(1.0f), 3.141592f*3.0f/2.0f, glm::vec3(0, 1,0)));
    }

}
