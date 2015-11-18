#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <string>

#include "include/GL/glew.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"

typedef unsigned int GLuint;


/******************************************************************************************
 *** Loads and stores gpu data from obj (object) + mtl (material) + dds (texture) files ***
 *** Just pass in the obj/mtl file path without extension (+ optional rotation) and it  ***
 *** will do the rest                                                                   ***
 ******************************************************************************************/

class ObjGPUData
{
    private:
        enum dataType : short;
        enum mtlDataType : short;
        struct FullVertex;

        void loadObject(char*);
        dataType getDataType(std::string);
        mtlDataType getMtlDataType(std::string);


    public:
        ObjGPUData(char*, float = 0.0f);

        struct Material{
            std::string materialName;
            GLfloat shine;
            glm::vec3 Ka, Kd, Ks;
            GLuint texture;
            std::string textureName;
            bool textureSet;

            Material(std::string materialName){
                this->materialName = materialName;
                textureSet = false;
            }
        };

        std::vector<glm::vec3> vList;
        std::vector<glm::vec2> vTextureList;
        std::vector<glm::vec3> vNormalList;
        std::vector<GLuint> fList;
        std::vector<int> materialIndices;
        std::vector<Material> materials;

        GLuint vertexArrayObj;
        GLuint elementBuffer;
        GLuint vertexBuffer;
        GLuint textureBuffer;
        GLuint normalBuffer;
        GLuint shaderProgram;
        GLuint texture_ID;
        GLuint MVP_ID, MV_ID, P_ID, N_ID;
        GLuint MTL_KA_ID, MTL_KD_ID, MTL_KS_ID, MTL_SHINE_ID;
        GLuint LPOS_ID, LA_ID, LD_ID, LS_ID;

        glm::mat4 unitScale;
        glm::mat4 scaling;
        glm::mat4 rotation;

        float whRatio;
};

#endif // OBJECT_H
