#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

#include "Surface.h"


/*! The Wall class implements wall objects.
 */
class Wall : public Surface
{

public:

    //! Wall constructor.
    /*!
      \param y1 The bottom y-coordinate of the wall.
      \param y2 The top y-coordinate of the wall.
      \param xmid The x-coordinate of the wall.
      \param thickness The horizontal thickness of the wall (default = 50.0).
    */
    Wall(float y1, float y2, float xmid, float thickness = 50.0f);

};

#endif // WALL_H_INCLUDED
