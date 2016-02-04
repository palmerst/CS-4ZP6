#include "Obj.h"

#include <iostream>

glm::mat4 Obj::matProjection = glm::mat4();
glm::mat4 Obj::matView = glm::mat4();
ObjGPUDataStore Obj::gpuStore;
ShaderStore Obj::shaderStore;
SoundStore Obj::soundStore;
Shader* Obj::currentShader = 0;

void Obj::render(glm::vec3 pos, float angle){

    for(int q = 0; q < gpuDataList.size(); q++){

        ObjGPUData* gpuData = gpuDataList[q];
        Shader* requiredShader = shaderList[q];

        if(currentShader != requiredShader){
            glUseProgram(requiredShader->shaderProgram);
            currentShader = requiredShader;
        }


        /*** Bind VAO associated w/ object ***/
        glBindVertexArray(gpuData->vertexArrayObj);

        /*** Iterate through all of the object pieces and render ***/
        for(int i = 0; i < gpuData->materialIndices.size()/2; i++){

            unsigned int first = (gpuData->materialIndices)[i*2];
            unsigned int last;

            if((2*i + 2) > (gpuData->materialIndices.size() - 1))
                last = gpuData->fList.size();
            else
                last = (gpuData->materialIndices)[i*2 + 2];

            unsigned int totalElements = last - first;

            /***  Bind the textures required by the object piece ***/
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, (gpuData->materials)[(gpuData->materialIndices)[i*2 + 1]].texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glUniform1i(currentShader->uniformIDMap.find("myTextureSampler")->second, 0);

            /***  Calculate transformations used in rendering the object piece and pass to shaders ***/
            glm::mat4 modelMat;
            if(transformOverrides)
                modelMat = glm::translate(glm::mat4(1.0f), pos + translationOverrideList[q]) * shearOverrideList[q] * glm::rotate(glm::mat4(1.0f), angle + rotationOverrideList[q], glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), modelScale) * gpuData->rotation * gpuData->unitScale;
            else
                modelMat = glm::translate(glm::mat4(1.0f), pos) * glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), modelScale) * gpuData->rotation * gpuData->unitScale;
            glm::mat4 modelViewMat = matView*modelMat;
            glm::mat4 MVP = matProjection*modelViewMat;
    //            glm::mat3 normalMat = glm::transpose(glm::inverse(glm::mat3(modelViewMat)));

            std::map<std::string, GLuint>::iterator uniformID;
            std::map<std::string, GLuint>::iterator mapEnd = currentShader->uniformIDMap.end();

            uniformID = currentShader->uniformIDMap.find("MVP");
            if(uniformID != mapEnd)
                glUniformMatrix4fv(currentShader->uniformIDMap.find("MVP")->second, 1, GL_FALSE, &MVP[0][0]);

//            uniformID = currentShader->uniformIDMap.find("ModelMatrix");
//            if(uniformID != mapEnd)
//                glUniformMatrix4fv(currentShader->uniformIDMap.find("ModelMatrix")->second, 1, GL_FALSE, &modelMat[0][0]);
    //            glUniformMatrix4fv(P_ID, 1, GL_FALSE, &mat_Projection[0][0]);
    //            glUniformMatrix3fv(N_ID, 1, GL_FALSE, &normalMat[0][0]);

            uniformID = currentShader->uniformIDMap.find("ModelMatrix");
            if(uniformID != mapEnd)
                glUniformMatrix4fv(currentShader->uniformIDMap.find("ModelMatrix")->second, 1, GL_FALSE, &modelMat[0][0]);
    //
    //            //  Pass material info to shaders
    //            glUniform3fv(currentGPUObj->MTL_KA_ID, 1, &((currentGPUObj->materials)[(currentGPUObj->materialIndices)[i*2 + 1]].Ka)[0]);
    //            glUniform3fv(currentGPUObj->MTL_KD_ID, 1, &((currentGPUObj->materials)[(currentGPUObj->materialIndices)[i*2 + 1]].Kd)[0]);
    //            glUniform3fv(currentGPUObj->MTL_KS_ID, 1, &((currentGPUObj->materials)[(currentGPUObj->materialIndices)[i*2 + 1]].Ks)[0]);
    //            glUniform1f(currentGPUObj->MTL_SHINE_ID, (currentGPUObj->materials)[(currentGPUObj->materialIndices)[i*2 + 1]].shine);

            //  Pass light info to shaders
    //            glm::vec4 sunLightPos_ViewSpace = viewMat * sunLightPos;    //  Transform sun position to view space
    //            glUniform4fv(obj->LPOS_ID, 1, &sunLightPos_ViewSpace[0]);
    //            glUniform3fv(obj->LA_ID, 1, &sunLightLa[0]);
    //            glUniform3fv(obj->LD_ID, 1, &sunLightLd[0]);
    //            glUniform3fv(obj->LS_ID, 1, &sunLightLs[0]);


            /*** Render the object piece ***/
            glDrawElements(GL_TRIANGLES, totalElements, GL_UNSIGNED_INT, (void*)(first * sizeof(GLuint)));

        }

    }

}
