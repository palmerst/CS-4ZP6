#ifndef ARCH_H_INCLUDED
#define ARCH_H_INCLUDED

#include "StandardObject.h"


/*! The Arch class implements the arch used to signify the stage goal.
 */
class Arch : public StandardObject
{

public:

    //! Arch constructor.
    /*!
      \param x The x coordinate of the arch.
      \param y The y coordinate of the arch.
      \param faceRight True if arch should face to the right (default false, i.e. facing left).
    */
    Arch(float x, float y, bool faceRight = false);

};


#endif // ARCH_H_INCLUDED
