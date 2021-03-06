#include "Obj.h"

#include <iostream>

glm::mat4 Obj::matProjection = glm::mat4();
glm::mat4 Obj::matView = glm::mat4();

glm::vec4 Obj::primaryLightPos(1000.0, 4000.0, -5000.0, 0);
glm::vec3 Obj::primaryLightLa(1.0, 1.0, 1.0);
glm::vec3 Obj::primaryLightLd(1.0, 1.0, 1.0);
glm::vec3 Obj::primaryLightLs(1.0, 1.0, 1.0);

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

            std::map<std::string, GLuint>::iterator uniformID;
            std::map<std::string, GLuint>::iterator mapEnd = currentShader->uniformIDMap.end();

            /***  Bind the textures required by the object piece ***/
            uniformID = currentShader->uniformIDMap.find("Texture");
            if(uniformID != mapEnd){
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, (gpuData->materials)[(gpuData->materialIndices)[i*2 + 1]].texture);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glUniform1i(currentShader->uniformIDMap.find("Texture")->second, 0);
            }

            uniformID = currentShader->uniformIDMap.find("Bump");
            if(uniformID != mapEnd){
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, (gpuData->materials)[(gpuData->materialIndices)[i*2 + 1]].bump);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glUniform1i(currentShader->uniformIDMap.find("Bump")->second, 1);
            }

            /***  Calculate transformations used in rendering the object piece and pass to shaders ***/
            glm::mat4 modelMat;
            if(transformOverrides)
                modelMat = glm::translate(glm::mat4(1.0f), pos + translationOverrideList[q]) * shearOverrideList[q] * glm::rotate(glm::mat4(1.0f), angle + rotationOverrideList[q], glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), modelScale) * gpuData->rotation * gpuData->unitScale;
            else
                modelMat = glm::translate(glm::mat4(1.0f), pos) * glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), modelScale) * gpuData->rotation * gpuData->unitScale;
            glm::mat4 modelViewMat = matView*modelMat;
            glm::mat4 MVP = matProjection*modelViewMat;
            glm::mat3 normalMat = glm::transpose(glm::inverse(glm::mat3(modelViewMat)));
            glm::vec4 primaryLightPos_ViewSpace = matView * primaryLightPos;

            uniformID = currentShader->uniformIDMap.find("MVP");
            if(uniformID != mapEnd)
                glUniformMatrix4fv(uniformID->second, 1, GL_FALSE, &MVP[0][0]);

            uniformID = currentShader->uniformIDMap.find("ModelViewMatrix");
            if(uniformID != mapEnd)
                glUniformMatrix4fv(uniformID->second, 1, GL_FALSE, &modelViewMat[0][0]);

            uniformID = currentShader->uniformIDMap.find("ModelMatrix");
            if(uniformID != mapEnd)
                glUniformMatrix4fv(uniformID->second, 1, GL_FALSE, &modelMat[0][0]);

            uniformID = currentShader->uniformIDMap.find("NormalMatrix");
            if(uniformID != mapEnd)
                glUniformMatrix3fv(uniformID->second, 1, GL_FALSE, &normalMat[0][0]);

            uniformID = currentShader->uniformIDMap.find("ProjectionMatrix");
            if(uniformID != mapEnd)
                glUniformMatrix4fv(uniformID->second, 1, GL_FALSE, &matProjection[0][0]);

            uniformID = currentShader->uniformIDMap.find("Material.Ka");
            if(uniformID != mapEnd)
                glUniform3fv(uniformID->second, 1, &((gpuData->materials)[(gpuData->materialIndices)[i*2 + 1]].Ka)[0]);

            uniformID = currentShader->uniformIDMap.find("Material.Kd");
            if(uniformID != mapEnd)
                glUniform3fv(uniformID->second, 1, &((gpuData->materials)[(gpuData->materialIndices)[i*2 + 1]].Kd)[0]);

            uniformID = currentShader->uniformIDMap.find("Material.Ks");
            if(uniformID != mapEnd)
                glUniform3fv(uniformID->second, 1, &((gpuData->materials)[(gpuData->materialIndices)[i*2 + 1]].Ks)[0]);

            uniformID = currentShader->uniformIDMap.find("Material.shine");
            if(uniformID != mapEnd)
                glUniform1f(uniformID->second, ((gpuData->materials)[(gpuData->materialIndices)[i*2 + 1]].shine));

            uniformID = currentShader->uniformIDMap.find("Light.Position");
            if(uniformID != mapEnd)
                glUniform4fv(uniformID->second, 1, &primaryLightPos_ViewSpace[0]);

            uniformID = currentShader->uniformIDMap.find("Light.La");
            if(uniformID != mapEnd)
                glUniform3fv(uniformID->second, 1, &primaryLightLa[0]);

            uniformID = currentShader->uniformIDMap.find("Light.Ld");
            if(uniformID != mapEnd)
                glUniform3fv(uniformID->second, 1, &primaryLightLd[0]);

            uniformID = currentShader->uniformIDMap.find("Light.Ls");
            if(uniformID != mapEnd)
                glUniform3fv(uniformID->second, 1, &primaryLightLs[0]);


            /*** Render the object piece ***/
            glDrawElements(GL_TRIANGLES, totalElements, GL_UNSIGNED_INT, (void*)(first * sizeof(GLuint)));

        }

    }

}
