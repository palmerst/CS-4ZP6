#ifndef SPEAR_H_INCLUDED
#define SPEAR_H_INCLUDED

#include "DynamicObject.h"
#include "StaticObject.h"

class Spear : public DynamicObject
{

public:

    Spear(float x, float y);

};


class Spears : public StaticObject
{

public:

    Spears(float x, float y);

};

#endif // SPEAR_H_INCLUDED
