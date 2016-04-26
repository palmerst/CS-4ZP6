#ifndef STANDARDOBJECT_H_INCLUDED
#define STANDARDOBJECT_H_INCLUDED

#include "Obj.h"

/*! The StandardObject class is derived from the Obj class and is the parent to all objects that do not take part in physics/collision calculations.
 */
class StandardObject : public Obj
{


public:

    glm::vec3 position;  //!< Object position
    float angle;  //!< Object rotation about z-axis

    void render();  //!< Renders the object

};

#endif // STANDARDOBJECT_H_INCLUDED
