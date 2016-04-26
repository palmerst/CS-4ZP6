#ifndef BOUNDARY_H_INCLUDED
#define BOUNDARY_H_INCLUDED

#include "Surface.h"

/*** Defines surface types (for adding different textures) ***/
enum BSurface
{
    BS_SAND
};

/*! The Boundary class implements the boundary that is used to create a surface which extends into the distance (i.e. creates the scene).
 */
class Boundary : public Surface
{

public:

    //! Boulder constructor.
    /*!
      \param x1 The leftmost extent of the boundary.
      \param x2 The rightmost extent of the boundary.
      \param y The y-coordinate of the boundary.
      \param surfaceType The type of surface.
    */
    Boundary(float x1, float x2, float y, BSurface surfaceType);

};

#endif // BOUNDARY_H_INCLUDED
