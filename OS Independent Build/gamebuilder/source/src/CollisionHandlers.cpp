#include "CollisionHandlers.h"

#include "Hero.h"
#include "Surface.h"

void setCollisionHandlers(cpSpace* space)
{
    cpCollisionHandler* colHand = cpSpaceAddCollisionHandler(space, OBJ_HERO, OBJ_BOULDER);
    colHand->beginFunc = (cpCollisionBeginFunc) begin_hero_boulder_collision;
    colHand->preSolveFunc = (cpCollisionPreSolveFunc) presolve_generic_hero_objectsurface;
    colHand->separateFunc = (cpCollisionSeparateFunc) separate_generic_hero_objectsurface;
    colHand = cpSpaceAddCollisionHandler(space, OBJ_HERO, OBJ_FATAL_HAZARD);
    colHand->beginFunc = (cpCollisionBeginFunc) begin_hero_fatal_collision;
    colHand = cpSpaceAddCollisionHandler(space, OBJ_HERO, OBJ_SURFACE);
    colHand->preSolveFunc = (cpCollisionPreSolveFunc) presolve_hero_surface;
    colHand->separateFunc = (cpCollisionSeparateFunc) separate_hero_surface;
    //  colHand = cpSpaceAddCollisionHandler(space, OBJ_HERO_BULLET, OBJ_SURFACE);
    // colHand->beginFunc = (cpCollisionBeginFunc) begin_single_deletion_collision;
    //  colHand = cpSpaceAddCollisionHandler(space, OBJ_HERO, OBJ_ENEMY);
    //  colHand->beginFunc = (cpCollisionBeginFunc) begin_knockback;
}

int begin_single_deletion_collision(cpArbiter *arb, cpSpace *space, void *unused)
{
    cpShape *a, *b;
    cpArbiterGetShapes(arb, &a, &b);

    cpSpaceAddPostStepCallback(space, (cpPostStepFunc)deleteObject, a, cpShapeGetUserData(a));

    return 0;
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
        return 0;
    }

    return 1;
}

int presolve_generic_hero_objectsurface(cpArbiter *arb, cpSpace *space, void *unused)
{
    cpShape *a, *b;
    cpArbiterGetShapes(arb, &a, &b);

    Hero* hero = static_cast<Hero*> (cpShapeGetUserData(a));

    if(cpvdot(cpArbiterGetNormal(arb), cpv(0, 1)) < 0)
    {
        hero->canJump = true;
    }

    return 1;
}

void separate_generic_hero_objectsurface(cpArbiter *arb, cpSpace *space, void *unused)
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
    PhysicsObject* pObj = static_cast<PhysicsObject*> (cpShapeGetUserData(b));

    if(!cpveql(pObj->deathNormal, cpvzero))
    {
        if(cpvdot(cpArbiterGetNormal(arb), pObj->deathNormal) < 0)
        {
            hero->death();
            return 0;
        }
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
    }

    return 1;
}

void separate_hero_surface(cpArbiter *arb, cpSpace *space, void *unused)
{
    CP_ARBITER_GET_SHAPES(arb, a, b);
    Hero* hero = static_cast<Hero*> (cpShapeGetUserData(a));
    hero->canJump = false;
}


//int begin_hero_boulder_collision(cpArbiter *arb, cpSpace *space, void *unused)
//{
//  cpShape *a, *b;
//  cpArbiterGetShapes(arb, &a, &b);
//
//  PhysicsObject* boulder = static_cast<PhysicsObject*> (cpShapeGetUserData(b));
//  PhysicsObject* hero = static_cast<PhysicsObject*> (cpShapeGetUserData(a));
//
//  cpVect bulVel = cpBodyGetVelocity(bullet->body);
//  cpVect enemyVel = cpBodyGetVelocity(enemy->body);
//  cpBodySetVelocity(enemy->body, cpvadd(enemyVel, cpvmult(cpvnormalize(bulVel), 150.0)));
//
//  cpSpaceAddPostStepCallback(space, (cpPostStepFunc)deleteObject, a, cpShapeGetUserData(a));
//
//  return 0;
//}

int begin_knockback(cpArbiter *arb, cpSpace *space, void *unused)
{
    cpShape *a, *b;
    cpArbiterGetShapes(arb, &a, &b);

    PhysicsObject* hero = static_cast<PhysicsObject*> (cpShapeGetUserData(a));

    cpVect heroVel = cpBodyGetVelocity(hero->body);

    cpBodySetVelocity(hero->body, cpvmult(cpvnormalize(cpvneg(heroVel)), 150.0));

    return 0;
}


void deleteObject(cpSpace *space, void *obj, void *data)
{

    PhysicsObject* temp = static_cast<PhysicsObject*>(data);

    if(cpSpaceContainsShape(space, temp->shape))
        cpSpaceRemoveShape(space, temp->shape);
    if(cpSpaceContainsBody(space, temp->body))
        cpSpaceRemoveBody(space, temp->body);

    temp->draw = false;
}
