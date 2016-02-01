#ifndef PHYSICSOBJECT_H_INCLUDED
#define PHYSICSOBJECT_H_INCLUDED

#include "include/chipmunk/chipmunk.h"
#include "Obj.h"
#include "CollisionHandlers.h"

class PhysicsObject : public Obj {

    public:

        static cpSpace* space;

        cpBody* body;           //!< Pointer to Chipmunk 2D body associated with the object.
        cpShape* shape;         //!< Pointer to Chipmunk 2D shape associated with the object.

        void render();

};

#endif // PHYSICSOBJECT_H_INCLUDED
