#ifndef KINEMATICOBJECT_H_INCLUDED
#define KINEMATICOBJECT_H_INCLUDED

#include "PhysicsObject.h"

/*! The KinematicObject class is derived from the PhysicsObject class.  This type of object is identical to static objects except that it can be moved by directly changing position, velocity, force, etc.
 */
class KinematicObject : public PhysicsObject
{

public:

    //! KinematicObject default constructor
    KinematicObject() {}

    //! KinematicObject constructor
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
    KinematicObject(float x, float y, float scale, float elast, float fric, int type, std::string gpuPath, std::string vPath, std::string fPath);

    //! Updates kinematic object (position, velocity, etc)
    /*!
      \param dt The timestep to move the object through.
    */
    virtual void update(float dt);
};

#endif // KINEMATICOBJECT_H_INCLUDED
