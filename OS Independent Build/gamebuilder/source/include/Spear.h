#ifndef SPEAR_H_INCLUDED
#define SPEAR_H_INCLUDED

#include "KinematicObject.h"
#include "StaticObject.h"


/*! The Spear class implements the spear hazard.
 */
class Spear : public KinematicObject
{

public:

    //! Spear constructor.
    /*!
      \param x The x coordinate of the spear.
      \param y The y coordinate of the spear.
      \param rotation The rotation of the spear about the z-axis.
    */
    Spear(float x, float y, float rotation = 0.0f);


};

#endif // SPEAR_H_INCLUDED
