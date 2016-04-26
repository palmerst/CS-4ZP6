#ifndef HERO_H_INCLUDED
#define HERO_H_INCLUDED

#include "DynamicObject.h"


/*! The Hero class implements the hero.
 */
class Hero : public DynamicObject
{

public:

    //! Hero constructor.
    /*!
      \param x The x coordinate of the hero.
      \param y The y coordinate of the hero.
    */
    Hero(float x, float y);

    cpVect startPos; //!< Hero starting position.
    bool dead;  //!< Flag indicates if the hero is dead.
    bool canJump;  //!< Flag indicates if the hero is currently allowed to jump.
    cpVect relVel;  //!< Velocity relative to the surface the hero is currently on (undefined if not on surface)
    bool levelWin;  //!< Flag indicates if hero has reached the goal.

    void death();  //!< Kills the hero and resets the stage.
    void jump();  //!< Makes the hero jump.
    void win();  //!< Play stage win fanfare and set the levelWin flag.

};


#endif // HERO_H_INCLUDED
