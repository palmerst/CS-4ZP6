#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED

#include "Surface.h"

/*! The Platform class implements platform objects.
 */
class Platform : public Surface
{

public:

    //! Platform constructor.
    /*!
      \param x1 The leftmost extent of the platform.
      \param x2 The rightmost extent of the platform.
      \param ymid The y-coordinate of the platform.
      \param thickness The vertical thickness of the platform (default = 50.0).
    */
    Platform(float x1, float x2, float ymid, float thickness = 50.0f);

};


#endif // PLATFORM_H_INCLUDED
