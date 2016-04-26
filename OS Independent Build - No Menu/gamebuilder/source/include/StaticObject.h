#ifndef STATICOBJECT_H_INCLUDED
#define STATICOBJECT_H_INCLUDED

#include "PhysicsObject.h"


/*! The StaticObject class is derived from the PhysicsObject class.  This type of object is subject only to collision calculations and may not be moved once placed in the space.
 */
class StaticObject : public PhysicsObject
{

public:
    //! StaticObject default constructor
    StaticObject() {}

    //! StaticObject constructor
    /*!
      \param x The x-coordinate of the dynamic object
      \param y The y-coordinate of the dynamic object
      \param scale Scalar factor by which to scale the object during GPU rendering
      \param elast Elasticity of the object
      \param fric Friction factor of the object
      \param type Type of object (different values affect collision routines)
      \param gpuPath The path to the obj file for the object
      \param vPath The path to the vertex shader for the object
      \param fPath The path to the fragment shader for the object
    */
    StaticObject(float x, float y, float scale, float elast, float fric, int type, std::string gpuPath, std::string vPath, std::string fPath);

};



#endif // STATICOBJECT_H_INCLUDED