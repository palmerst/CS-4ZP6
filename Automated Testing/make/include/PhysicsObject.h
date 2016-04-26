#ifndef PHYSICSOBJECT_H_INCLUDED
#define PHYSICSOBJECT_H_INCLUDED

#include "chipmunk/chipmunk.h"
#include "Obj.h"
#include "CollisionHandlers.h"


/*! The PhysicsObject class is derived from the Obj class and is the parent to all objects associated with Chipmunk2D.
 */
class PhysicsObject : public Obj
{

public:

    //! PhysicsObject constructor
    virtual ~PhysicsObject();

    static cpSpace* space;  //!< Pointer to current Chipmunk 2D space.

    cpBody* body;           //!< Pointer to Chipmunk 2D body associated with the object.
    cpShape* shape;         //!< Pointer to Chipmunk 2D shape associated with the object.

    cpVect standingNormal;  //!< Normal used in collision handler to determine if hero can jump.
    cpVect deathNormal;     //!< Normal used in collision handler to determine if hero should be killed.


    void render();      //!< Renders the object.

};

#endif // PHYSICSOBJECT_H_INCLUDED
