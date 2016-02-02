#ifndef HERO_H_INCLUDED
#define HERO_H_INCLUDED

#include "DynamicObject.h"

class Hero : public DynamicObject {

    public:

        Hero(float x, float y);

        cpVect startPos;

};


#endif // HERO_H_INCLUDED
