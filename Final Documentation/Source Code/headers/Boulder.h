#ifndef BOULDER_H_INCLUDED
#define BOULDER_H_INCLUDED

#include "DynamicObject.h"

/*! The Boulder class implements the boulder hazard.
 */

class Boulder : public DynamicObject
{

public:

    //! Boulder constructor.
    /*!
      \param x The x coordinate of the boulder.
      \param y The y coordinate of the boulder.
    */
    Boulder(float x, float y);

};

#endif // BOULDER_H_INCLUDED
