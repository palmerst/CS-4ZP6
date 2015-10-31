#ifndef OBJ_H_INCLUDED
#define OBJ_H_INCLUDED

#include "include/chipmunk/chipmunk.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"

#include <vector>

typedef std::vector<glm::vec3> vertexList;
typedef std::vector<unsigned int> faceList;

enum Static_Obj_Type {
    STATIC_BOUNDARY,
    STATIC_PLATFORM
};

enum Dynamic_Obj_Type {
    DYNAMIC_CHARACTER
};

class Obj {

    public:

        cpBody* body;
        cpShape* shape;

};

class Static_Obj : public Obj {

    public:

        struct {
            unsigned int first, len;
        } bufferLocation;


};

class Boundary : public Static_Obj {

    public:
        Boundary(cpSpace*, vertexList&, cpVect, cpVect);


};

class Platform {

};

class Dynamic_Obj : public Obj {

    public:

        unsigned int masterIndex;

};

class Character : public Dynamic_Obj {

    public:

        Character(cpSpace*, glm::vec2);

};

#endif // STATIC_OBJ_H_INCLUDED
