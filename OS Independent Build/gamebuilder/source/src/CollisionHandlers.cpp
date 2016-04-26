#include "CollisionHandlers.h"

#include "Hero.h"
#include "Surface.h"
#include "MovingPlatform.h"

#include <iostream>

void setCollisionHandlers(cpSpace* space)
{
    cpCollisionHandler* colHand = cpSpaceAddCollisionHandler(space, OBJ_HERO, OBJ_BOULDER);
    colHand->beginFunc = (cpCollisionBeginFunc) begin_hero_boulder_collision;
    colHand->preSolveFunc = (cpCollisionPreSolveFunc) presolve_hero_dynamic_objectsurface;
    colHand->separateFunc = (cpCollisionSeparateFunc) separate_hero_objectsurface;
    colHand = cpSpaceAddCollisionHandler(space, OBJ_HERO, OBJ_FATAL_HAZARD);
    colHand->beginFunc = (cpCollisionBeginFunc) begin_hero_fatal_collision;
    colHand->preSolveFunc = (cpCollisionPreSolveFunc) presolve_hero_kinematic_objectsurface;
    colHand->separateFunc = (cpCollisionSeparateFunc) separate_hero_objectsurface;
    colHand = cpSpaceAddCollisionHandler(space, OBJ_HERO, OBJ_SURFACE);
    colHand->preSolveFunc = (cpCollisionPreSolveFunc) presolve_hero_surface;
    colHand->separateFunc = (cpCollisionSeparateFunc) separate_hero_surface;
    colHand = cpSpaceAddCollisionHandler(space, OBJ_HERO, OBJ_MOVINGPLAT);
    colHand->preSolveFunc = (cpCollisionPreSolveFunc) presolve_hero_movingplat;
    colHand->separateFunc = (cpCollisionSeparateFunc) separate_hero_surface;
    colHand = cpSpaceAddCollisionHandler(space, OBJ_HERO, OBJ_GOAL);
    colHand->preSolveFunc = (cpCollisionPreSolveFunc) presolve_hero_goal;

}

int begin_hero_boulder_collision(cpArbiter *arb, cpSpace *space, void *unused)
{
    cpShape *a, *b;
    cpArbiterGetShapes(arb, &a, &b);

    Hero* hero = static_cast<Hero*> (cpShapeGetUserData(a));
    PhysicsObject* boulder = static_cast<PhysicsObject*> (cpShapeGetUserData(b));

    if(cpvlength(cpBodyGetVelocity(boulder->body)) > 500.0f)
    {

        hero->death();
        return 1;
    }

    return 1;
}

int presolve_hero_dynamic_objectsurface(cpArbiter *arb, cpSpace *space, void *unused)
{
    cpShape *a, *b;
    cpArbiterGetShapes(arb, &a, &b);

    Hero* hero = static_cast<Hero*> (cpShapeGetUserData(a));
    DynamicObject* dynObj = static_cast<DynamicObject*> (cpShapeGetUserData(b));

    if(cpvdot(cpArbiterGetNormal(arb), cpv(0, 1)) < 0)
    {
        hero->canJump = true;
        hero->relVel = cpBodyGetVelocity(dynObj->body);
    }

    return 1;
}

int presolve_hero_kinematic_objectsurface(cpArbiter *arb, cpSpace *space, void *unused)
{
    cpShape *a, *b;
    cpArbiterGetShapes(arb, &a, &b);

    Hero* hero = static_cast<Hero*> (cpShapeGetUserData(a));
    KinematicObject* kinObj = static_cast<KinematicObject*> (cpShapeGetUserData(b));

    if(cpvdot(cpArbiterGetNormal(arb), cpv(0, 1)) < 0)
    {
        hero->canJump = true;
        hero->relVel = cpBodyGetVelocity(kinObj->body);
    }

    return 1;
}

void separate_hero_objectsurface(cpArbiter *arb, cpSpace *space, void *unused)
{
    cpShape *a, *b;
    cpArbiterGetShapes(arb, &a, &b);

    Hero* hero = static_cast<Hero*> (cpShapeGetUserData(a));

    hero->canJump = false;
}


int begin_hero_fatal_collision(cpArbiter *arb, cpSpace *space, void *unused)
{
    cpShape *a, *b;
    cpArbiterGetShapes(arb, &a, &b);

    Hero* hero = static_cast<Hero*> (cpShapeGetUserData(a));
    KinematicObject* pObj = static_cast<KinematicObject*> (cpShapeGetUserData(b));

    if(!cpveql(pObj->deathNormal, cpvzero))
    {
        if(cpvdot(cpArbiterGetNormal(arb), pObj->deathNormal) < 0)
        {
            hero->death();
            return 1;
        }
    }

    return 1;
}


int presolve_hero_movingplat(cpArbiter *arb, cpSpace *space, void *unused)
{
    CP_ARBITER_GET_SHAPES(arb, a, b);
    Hero* hero = static_cast<Hero*> (cpShapeGetUserData(a));
    MovingPlatform* mp = static_cast<MovingPlatform*> (cpShapeGetUserData(b));

    if(cpvdot(cpArbiterGetNormal(arb), mp->standingNormal) < 0)
    {
        hero->canJump = true;
        hero->relVel = cpBodyGetVelocity(mp->body);
    }

    return 1;
}

int presolve_hero_surface(cpArbiter *arb, cpSpace *space, void *unused)
{
    CP_ARBITER_GET_SHAPES(arb, a, b);
    Hero* hero = static_cast<Hero*> (cpShapeGetUserData(a));
    Surface* surface = static_cast<Surface*> (cpShapeGetUserData(b));

    if(cpvdot(cpArbiterGetNormal(arb), surface->standingNormal) < 0)
    {
        hero->canJump = true;
        hero->relVel = cpBodyGetVelocity(surface->body);
    }

    return 1;
}

void separate_hero_surface(cpArbiter *arb, cpSpace *space, void *unused)
{
    CP_ARBITER_GET_SHAPES(arb, a, b);
    Hero* hero = static_cast<Hero*> (cpShapeGetUserData(a));
    hero->canJump = false;
}


int presolve_hero_goal(cpArbiter *arb, cpSpace *space, void *unused)
{
    CP_ARBITER_GET_SHAPES(arb, a, b);
    Hero* hero = static_cast<Hero*> (cpShapeGetUserData(a));
    Surface* surface = static_cast<Surface*> (cpShapeGetUserData(b));

    if(cpvdot(cpArbiterGetNormal(arb), surface->standingNormal) < 0)
    {
        hero->win();
    }

    return 1;
}
