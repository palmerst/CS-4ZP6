#ifndef ENVIRONMENT_H_INCLUDED
#define ENVIRONMENT_H_INCLUDED

#include "include/GL/glew.h"
#include "include/chipmunk/chipmunk.h"
#include "Obj.h"
#include "ObjGPUData.h"


/*** In game environment ***/

class Environment {

    private:

        cpSpace* envSpace;

        /*** Objects in environment ***/
        std::vector<Boundary> boundaries;
        std::vector<DynamicObject> dynamicObjects;

        /*** Shader handles/identifiers ***/
        GLuint shaderProgram;
        GLuint MVP_ID, MV_ID, M_ID, P_ID, N_ID, MTL_KA_ID, MTL_KD_ID, MTL_KS_ID, MTL_SHINE_ID, LPOS_ID, LA_ID, LD_ID, LS_ID, texture_ID;
        GLuint subroutine_object, subroutine_boundary_xy, subroutine_boundary_yz, subroutine_boundary_xz;

        /*** Projection and view matrices ***/
        glm::mat4 mat_Projection;
        glm::mat4 mat_View;

        /*** Draw an object ***/
        void drawObj(Obj, bool = false);

    public:

        Environment();

        /*** Adds a box boundary from p1 (lower left) to p2 (upper right) ***
         *** Links to gpu data representing the boundary visuals          ***/
        void addBoundary(cpVect p1, cpVect p2, ObjGPUData*);

        /*** Adds a dynamic object with centroid at position and links to gpu data ***/
        void addDynamicObject(glm::vec2 pos, ObjGPUData*);

        /*** Step the space through time dt ***/
        void updateEnvironment(double dt);

        /*** Draw all objects/boundaries in the environment ***/
        void drawEnvironment();

        /*** Update projection matrix ***/
        void updateProjection(glm::mat4);

};

#endif // ENVIRONMENT_H_INCLUDED
