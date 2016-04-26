#ifndef GOAL_H_INCLUDED
#define GOAL_H_INCLUDED

#include "Surface.h"


/*! The Goal class implements the checkered goal platform.
 */
class Goal : public Surface
{

public:

    //! Goal constructor.
    /*!
      \param x1 The leftmost extent of the goal.
      \param x2 The rightmost extent of the goal.
      \param ymid The y-coordinate of the goal.
      \param thickness The vertical thickness of the goal (default = 50.0).
    */
    Goal(float x1, float x2, float ymid, float thickness = 50.0f);

};

#endif // GOAL_H_INCLUDED
