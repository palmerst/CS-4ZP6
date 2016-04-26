#ifndef SKYBOX_H_INCLUDED
#define SKYBOX_H_INCLUDED

#include "StandardObject.h"

/*! The Skybox class implements the skybox used to provide the backdrop of the stage.
 */
class Skybox : public StandardObject
{

public:

    //! Skybox constructor.
    /*!
      \param x The x coordinate of the skybox.
      \param y The y coordinate of the skybox.
      \param bgNum Int corresponding to the desired backdrop.
    */
    Skybox(float x, float y, int bgNum);

};

#endif // SKYBOX_H_INCLUDED
