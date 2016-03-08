#ifndef SURFACE_H_INCLUDED
#define SURFACE_H_INCLUDED

#include "StaticObject.h"

/*! The StaticObject class is derived from the Obj class.  Physics calculations are generally ignored for static objects.  Used primarily for boundaries and stationary platforms.
 */
class Surface : public StaticObject
{

public:
    //! StaticObject constructor
    /*!
      \param space Chipmunk 2D space to attach object to
      \param p1 Bottom left coordinate of bounding box
      \param p2 Upper right coordinate of bounding box
      \param gpuData Pointer to the gpu data associated with the object
    */
    Surface(cpVect p1, cpVect p2, bool isRamp, float thickness = 50.0f);


};

#endif // SURFACE_H_INCLUDED
