#ifndef KINEMATICOBJECT_H_INCLUDED
#define KINEMATICOBJECT_H_INCLUDED

#include "PhysicsObject.h"

/*! The KinematicObject class is derived from the Obj class.  This type of object has features of both static objects and dynamic objects and is generally used for moving platforms.
 */
class KinematicObject : public PhysicsObject {

    public:
        //! DynamicObject constructor
        /*!
          \param space Chipmunk 2D space to attach object to
          \param p1 Bottom left coordinate of bounding box
          \param p2 Upper right coordinate of bounding box
          \param gpuData Pointer to the gpu data associated with the object
          \param type Type of object (different values affect collision routines)
        */
        KinematicObject(cpSpace* space, cpVect p1, cpVect p2, ObjGPUData* gpuData, int type);

};

#endif // KINEMATICOBJECT_H_INCLUDED
