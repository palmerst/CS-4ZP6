#ifndef OBJ_H_INCLUDED
#define OBJ_H_INCLUDED

#include "include/chipmunk/chipmunk.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "ObjGPUData.h"

#include <vector>

class Obj {

    public:

        cpBody* body;
        cpShape* shape;
        ObjGPUData* gpuData;

        float height, width;

};

class Boundary : public Obj {

    public:
        Boundary(cpSpace*, cpVect, cpVect, ObjGPUData*);


};

class DynamicObject : public Obj {

    public:
        DynamicObject();
        DynamicObject(cpSpace*, glm::vec2, float, float, float, float, ObjGPUData*, bool = false);

};


#endif // STATIC_OBJ_H_INCLUDED
