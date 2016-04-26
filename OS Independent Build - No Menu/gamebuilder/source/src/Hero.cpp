#include "Hero.h"

Hero::Hero(float x, float y) : DynamicObject(x, y, 200.0f, 100.0f, 0.0f, 1.0f, OBJ_HERO, "./data/obj/testchar", "./data/shader/vObject.glsl", "./data/shader/fObject.glsl")
{

    cpBodySetMoment(body, INFINITY);
    startPos = cpv(x, y);

    canJump = false;
    levelWin = false;
    dead = false;

}

void Hero::death()
{

    Sound* sound = soundStore.add("./data/sound/scream.wav");
    sound->play();
    dead = true;

}


void Hero::jump()
{
    cpVect vel = cpBodyGetVelocity(body);

    if(canJump){
        cpBodySetVelocity(body, cpv(vel.x, relVel.y + 1150.0));
    }

}

void Hero::win(){

    if(levelWin)
        return;
    levelWin = true;
    Sound* sound = soundStore.add("./data/sound/fanfare.wav");
    sound->play();
    cpBodySetVelocity(body, cpvzero);
    cpBodySetForce(body, cpvzero);
}
