#ifndef COLLISIONHANDLERS_H_INCLUDED
#define COLLISIONHANDLERS_H_INCLUDED

#include "PhysicsObject.h"

void setCollisionHandlers(cpSpace*);

int begin_single_deletion_collision(cpArbiter*, cpSpace*, cpDataPointer);
int begin_hero_boulder_collision(cpArbiter*, cpSpace*, cpDataPointer);
int begin_hero_fatal_collision(cpArbiter*, cpSpace*, cpDataPointer);
int presolve_hero_surface(cpArbiter*, cpSpace*, cpDataPointer);
int presolve_hero_movingplat(cpArbiter*, cpSpace*, cpDataPointer);
void separate_hero_surface(cpArbiter*, cpSpace*, cpDataPointer);
int begin_knockback(cpArbiter*, cpSpace*, void*);

int presolve_hero_dynamic_objectsurface(cpArbiter*, cpSpace*, cpDataPointer);
int presolve_hero_kinematic_objectsurface(cpArbiter*, cpSpace*, cpDataPointer);
void separate_hero_objectsurface(cpArbiter*, cpSpace*, cpDataPointer);

void deleteObject(cpSpace *space, void *obj, void *data);

#endif // COLLISIONHANDLERS_H_INCLUDED
