#ifndef RAMP_H_INCLUDED
#define RAMP_H_INCLUDED

#include "Surface.h"


/*! The Ramp class implements ramp objects.
 */
class Ramp : public Surface
{

public:

    //! Ramp constructor.
    /*!
      \param x1 The leftmost extent of the ramp.
      \param x2 The rightmost extent of the ramp.
      \param y1 The bottom y-coordinate of the ramp.
      \param y2 The top y-coordinate of the ramp.
      \param thickness The thickness of the ramp (default = 50.0).
    */
    Ramp(float x1, float x2, float y1, float y2, float thickness = 50.0f);

};

#endif // RAMP_H_INCLUDED
