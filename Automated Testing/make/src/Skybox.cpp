#include "Skybox.h"


Skybox::Skybox(float x, float y, int bgNum)
{
    position = glm::vec3(x, y, 0);
    angle = 0;

    modelScale = glm::vec3(15000.0f);

    draw = true;
    transformOverrides = true;
    translationOverrideList.push_back(glm::vec3());
    rotationOverrideList.push_back(0.0f);

    shaderList.push_back(shaderStore.add("./data/shader/vSkybox.glsl", "./data/shader/fSkybox.glsl"));

    if(bgNum < 1)
        bgNum = 1;
    if(bgNum > 2)
        bgNum = 2;

    if(bgNum == 1)
    {
        gpuDataList.push_back(gpuStore.add("./data/obj/skybox"));
        shearOverrideList.push_back(glm::rotate(glm::mat4(1.0f), -3.141592f/12.0f, glm::vec3(1,0,0)));
    }

    if(bgNum == 2)
    {
        gpuDataList.push_back(gpuStore.add("./data/obj/skybox2"));
        shearOverrideList.push_back(glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1,0,0)));
    }
}
