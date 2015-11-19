#include "Obj.h"

#include <iostream>

void setCollisionHandlers(cpSpace* space){
    cpCollisionHandler* colHand = cpSpaceAddCollisionHandler(space, OBJ_HERO_BULLET, OBJ_ENEMY);
    colHand->beginFunc = (cpCollisionBeginFunc) begin_enemy_bullet_collision;
    colHand = cpSpaceAddCollisionHandler(space, OBJ_HERO_BULLET, OBJ_BOUNDARY);
    colHand->beginFunc = (cpCollisionBeginFunc) begin_single_deletion_collision;
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

int begin_enemy_bullet_collision(cpArbiter *arb, cpSpace *space, void *unused)
{
  cpShape *a, *b;
  cpArbiterGetShapes(arb, &a, &b);

  DynamicObject* enemy = static_cast<DynamicObject*> (cpShapeGetUserData(b));
  DynamicObject* bullet = static_cast<DynamicObject*> (cpShapeGetUserData(a));

  cpVect bulVel = cpBodyGetVelocity(bullet->body);
  cpVect enemyVel = cpBodyGetVelocity(enemy->body);
  cpBodySetVelocity(enemy->body, cpvadd(enemyVel, cpvmult(cpvnormalize(bulVel), 150.0)));

  cpSpaceAddPostStepCallback(space, (cpPostStepFunc)deleteObject, a, cpShapeGetUserData(a));

  return 0;
}

int begin_knockback(cpArbiter *arb, cpSpace *space, void *unused)
{
  cpShape *a, *b;
  cpArbiterGetShapes(arb, &a, &b);

  DynamicObject* hero = static_cast<DynamicObject*> (cpShapeGetUserData(a));

  cpVect heroVel = cpBodyGetVelocity(hero->body);

  cpBodySetVelocity(hero->body, cpvmult(cpvnormalize(cpvneg(heroVel)), 150.0));

  return 0;
}


void deleteObject(cpSpace *space, void *obj, void *data){

    DynamicObject* temp = static_cast<DynamicObject*>(data);

    if(cpSpaceContainsShape(space, temp->shape))
        cpSpaceRemoveShape(space, temp->shape);
    if(cpSpaceContainsBody(space, temp->body))
        cpSpaceRemoveBody(space, temp->body);

    temp->draw = false;
}


/*** Boundary object ***/
Boundary::Boundary(cpSpace* space, cpVect p1, cpVect p2, ObjGPUData* gpuData){

    /*** Set physics data ***/
    body = cpSpaceAddBody(space, cpBodyNewStatic());
    cpBodySetPosition(body, cpvlerp(p1,p2,0.50f));
    shape = cpSpaceAddShape(space, cpBoxShapeNew(body, p2.x - p1.x, p2.y - p1.y, 0.1f));
	cpShapeSetElasticity(shape, 0.5f);
	cpShapeSetFriction(shape, 1.0f);
	height = p2.y - p1.y;
	width = p2.x - p1.x;

	cpShapeSetCollisionType(shape, OBJ_BOUNDARY);

    /*** Link gpu data ***/
    this->gpuData = gpuData;

    draw = true;

}


/*** Generic dynamic object ***/
DynamicObject::DynamicObject(){
    body = 0;
    shape = 0;
}

DynamicObject::DynamicObject(cpSpace* space, glm::vec2 pos, float mass, float scale, float elast, float fric, ObjGPUData* gpuData, int type, bool noRotation){

    height = scale;
	width = scale*gpuData->whRatio;

    /*** Set physics data ***/
    if(noRotation)
        body = cpBodyNew(mass, INFINITY);
    else{
        body = cpBodyNew(mass, cpMomentForBox(mass, width, height));
    }
    cpSpaceAddBody(space, body);
    cpBodySetPosition(body, cpv(pos.x, pos.y));
    shape = cpSpaceAddShape(space, cpBoxShapeNew(body, width, height, 0.01));
	cpShapeSetElasticity(shape, elast);
	cpShapeSetFriction(shape, fric);
	cpShapeSetUserData(shape, this);
    cpShapeSetCollisionType(shape, type);

    /*** Link gpu data ***/
    this->gpuData = gpuData;

    draw = true;
}
