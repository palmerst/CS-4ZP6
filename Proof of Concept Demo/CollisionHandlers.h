#ifndef COLLISIONHANDLERS_H_INCLUDED
#define COLLISIONHANDLERS_H_INCLUDED

#include "PhysicsObject.h"

void setCollisionHandlers(cpSpace*);

int begin_single_deletion_collision(cpArbiter*, cpSpace*, cpDataPointer);
int begin_hero_boulder_collision(cpArbiter*, cpSpace*, cpDataPointer);
int begin_knockback(cpArbiter*, cpSpace*, void*);

void deleteObject(cpSpace *space, void *obj, void *data);

#endif // COLLISIONHANDLERS_H_INCLUDED
