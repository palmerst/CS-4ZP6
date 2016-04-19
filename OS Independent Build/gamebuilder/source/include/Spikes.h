#ifndef SPIKES_H_INCLUDED
#define SPIKES_H_INCLUDED

#include "KinematicObject.h"

class Spikes : public KinematicObject
{

public:

    Spikes(float x, float y, float rotation = 0.0f);
    void update(float dt);

};

#endif // SPIKES_H_INCLUDED
