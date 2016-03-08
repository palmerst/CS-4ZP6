#ifndef STANDARDOBJECT_H_INCLUDED
#define STANDARDOBJECT_H_INCLUDED

#include "Obj.h"

class StandardObject : public Obj
{


public:

    glm::vec3 position;
    float angle;

    void render();

};

#endif // STANDARDOBJECT_H_INCLUDED
