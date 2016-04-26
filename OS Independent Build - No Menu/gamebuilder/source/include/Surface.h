#ifndef SURFACE_H_INCLUDED
#define SURFACE_H_INCLUDED

#include "StaticObject.h"

/*! The Surface class is derived from the StaticObject class.  Used primarily for stationary platforms.
 */
class Surface : public StaticObject
{

public:
    //! Surface constructor
    /*!
      \param p1 Bottom left coordinate of bounding box
      \param p2 Upper right coordinate of bounding box
      \param isRamp Flag specifies if surface is a ramp
      \param thickness Thickness of the surface
    */
    Surface(cpVect p1, cpVect p2, bool isRamp, float thickness = 50.0f);


};

#endif // SURFACE_H_INCLUDED
