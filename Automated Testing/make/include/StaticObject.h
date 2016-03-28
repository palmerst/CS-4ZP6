#ifndef STATICOBJECT_H_INCLUDED
#define STATICOBJECT_H_INCLUDED

#include "PhysicsObject.h"


/*! The DynamicObject class is derived from the Obj class.  This type of object is subject to all physics calculations.
 */
class StaticObject : public PhysicsObject
{

public:
    //! DynamicObject constructor
    StaticObject() {}
    //! DynamicObject constructor
    /*!
      \param space Chipmunk 2D space to attach object to
      \param pos Coordinates of the initial center of the object
      \param mass Mass of the object
      \param scale Scalar factor by which to scale the object during GPU rendering
      \param elast Elasticity of the object
      \param fric Friction factor of the object
      \param gpuData Pointer to the gpu data associated with the object
      \param type Type of object (different values affect collision routines)
      \param noRotation Flag to ignore angular momentum in the physics calculations (default = false)
    */
    StaticObject(float x, float y, float scale, float elast, float fric, int type, std::string gpuPath, std::string vPath, std::string fPath, float angle = 0.0f);

};



#endif // STATICOBJECT_H_INCLUDED
