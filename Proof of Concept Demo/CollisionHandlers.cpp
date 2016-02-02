#include "CollisionHandlers.h"

#include "Hero.h"

void setCollisionHandlers(cpSpace* space){
    cpCollisionHandler* colHand = cpSpaceAddCollisionHandler(space, OBJ_HERO, OBJ_BOULDER);
    colHand->beginFunc = (cpCollisionBeginFunc) begin_hero_boulder_collision;
  //  colHand = cpSpaceAddCollisionHandler(space, OBJ_HERO_BULLET, OBJ_BOUNDARY);
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

  if(cpvlength(cpBodyGetVelocity(boulder->body)) > 500.0f){

      cpBodySetPosition(hero->body, hero->startPos);
      cpBodySetVelocity(hero->body, cpvzero);
        return 0;
  }

  return 1;
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


void deleteObject(cpSpace *space, void *obj, void *data){

    PhysicsObject* temp = static_cast<PhysicsObject*>(data);

    if(cpSpaceContainsShape(space, temp->shape))
        cpSpaceRemoveShape(space, temp->shape);
    if(cpSpaceContainsBody(space, temp->body))
        cpSpaceRemoveBody(space, temp->body);

    temp->draw = false;
}
