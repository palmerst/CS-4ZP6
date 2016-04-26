#ifndef DYNAMICOBJECT_H_INCLUDED
#define DYNAMICOBJECT_H_INCLUDED

#include "PhysicsObject.h"

/*! The DynamicObject class is derived from the PhysicsObject class.  This type of object is subject to all physics calculations.
 */
class DynamicObject : public PhysicsObject
{

public:
    //! DynamicObject default constructor
    DynamicObject();
    //! DynamicObject constructor
    /*!
      \param x The x-coordinate of the dynamic object
      \param y The y-coordinate of the dynamic object
      \param scale Scalar factor by which to scale the object during GPU rendering
      \param mass Mass of the object
      \param elast Elasticity of the object
      \param fric Friction factor of the object
      \param type Type of object (different values affect collision routines)
      \param gpuPath The path to the obj file for the object
      \param vPath The path to the vertex shader for the object
      \param fPath The path to the fragment shader for the object
    */
    DynamicObject(float x, float y, float scale, float mass, float elast, float fric, int type, std::string gpuPath, std::string vPath, std::string fPath);

};

#endif // DYNAMICOBJECT_H_INCLUDED
