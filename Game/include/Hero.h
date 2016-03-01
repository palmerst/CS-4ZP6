#ifndef HERO_H_INCLUDED
#define HERO_H_INCLUDED

#include "DynamicObject.h"

class Hero : public DynamicObject {

    public:

        Hero(float x, float y);

        cpVect startPos;

        void death();

        bool canJump;

};


#endif // HERO_H_INCLUDED
