#ifndef OBJ_H_INCLUDED
#define OBJ_H_INCLUDED

#include "include/chipmunk/chipmunk.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "ObjGPUData.h"

#include <vector>

#define OBJ_BOUNDARY 0x0001
#define OBJ_ENEMY 0x0002
#define OBJ_HERO 0x0004
#define OBJ_HERO_BULLET 0x0008


void setCollisionHandlers(cpSpace*);

int begin_single_deletion_collision(cpArbiter*, cpSpace*, cpDataPointer);
int begin_enemy_bullet_collision(cpArbiter*, cpSpace*, cpDataPointer);

void deleteObject(cpSpace *space, void *obj, void *data);

class Obj {

    public:

        cpBody* body;
        cpShape* shape;
        ObjGPUData* gpuData;

        float height, width;

        bool draw;

};

class Boundary : public Obj {

    public:
        Boundary(cpSpace*, cpVect, cpVect, ObjGPUData*);


};

class DynamicObject : public Obj {

    public:
        DynamicObject();
        DynamicObject(cpSpace*, glm::vec2, float, float, float, float, ObjGPUData*, int, bool = false);

};


#endif // STATIC_OBJ_H_INCLUDED
