#ifndef SPIKES_H_INCLUDED
#define SPIKES_H_INCLUDED

#include "KinematicObject.h"

/*! The Spikes class implements the spikes hazard.
 */
class Spikes : public KinematicObject
{

public:

    //! Spikes constructor.
    /*!
      \param x The x coordinate of the spikes.
      \param y The y coordinate of the spikes.
      \param rotation The rotation of the spikes about the z-axis.
    */
    Spikes(float x, float y, float rotation = 0.0f);

};

#endif // SPIKES_H_INCLUDED
