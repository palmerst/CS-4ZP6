#ifndef ENVIRONMENT_H_INCLUDED
#define ENVIRONMENT_H_INCLUDED

#include "include/GL/glew.h"
#include "include/chipmunk/chipmunk.h"
#include "Obj.h"
#include "Loader.h"

class Environment {

    private:

        cpSpace* envSpace;

        std::vector<Static_Obj*> staticObjects;
        vertexList staticMasterVertexList;
        GLuint staticVAO;
        GLuint staticVBO;
        void updateStaticObjectBufferData();

        std::vector<Dynamic_Obj*> dynamicObjects;
        std::vector<GLuint>* masterObjectVAOList;

        GLuint shader;
        GLuint MVP_ID;

        glm::mat4 mat_Projection;

    public:

        Environment(std::vector<GLuint>*);
        void addStaticObject(cpVect, cpVect, Static_Obj_Type);
        void addDynamicObject(glm::vec2, Dynamic_Obj_Type);
        void updateEnvironment();
        void drawEnvironment();
        void updateProjection(glm::mat4);

};

#endif // ENVIRONMENT_H_INCLUDED
