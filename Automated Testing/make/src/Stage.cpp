#include "Stage.h"
#include "StageLoader.h"
#include <iostream>
#include "Menu.h"

Stage::Stage(std::string stageName)
{

    /*** Set up space variables ***/
    envSpace = cpSpaceNew();
    cpSpaceSetIterations(envSpace, 10);
    cpSpaceSetGravity(envSpace, cpv(0, -1500));
    PhysicsObject::space = envSpace;

    /*** Set up projection and view matrices ***/
    Obj::matProjection = glm::perspective(60.0f*3.1415f/180.0f, Environment::screenWidth/Environment::screenHeight, 10.0f, 30000.0f);

    overlay = new Menu(true);
    nextEnv = 0;

    setCollisionHandlers(envSpace);

    StageLoader* ns = new StageLoader(stageName.c_str(), physicsObjects, kinematicObjects, standardObjects, skybox, boundary, userControlObject);

    soundMap.insert(std::pair<std::string, Sound*>("Background", new Sound("./data/sound/bm.wav")));
    soundMap.insert(std::pair<std::string, Sound*>("Jump", new Sound("./data/sound/jump.wav")));

    soundMap.find("Background")->second->play(1);

    winTimer = -1;

    this->stageName = stageName;
}

Stage::~Stage()
{
    cpSpaceFree(envSpace);

    while(!standardObjects.empty())
    {
        delete standardObjects.back();
        standardObjects.pop_back();
    }

    while(!physicsObjects.empty())
    {
        delete physicsObjects.back();
        physicsObjects.pop_back();
    }

    while(!kinematicObjects.empty())
    {
        delete kinematicObjects.back();
        kinematicObjects.pop_back();
    }

    delete boundary;
    delete userControlObject;
    delete skybox;
    delete overlay;

    soundMap.find("Background")->second->stop();
}

void Stage::processContinuousInput()
{
    if(userControlObject->levelWin)
        return;

    if(keyStates[GLFW_KEY_A] || keyStates[GLFW_KEY_LEFT])
    {
        cpVect curVel = cpBodyGetVelocity(userControlObject->body);
        if(curVel.x > 0)
            cpBodySetVelocity(userControlObject->body, cpv(0, curVel.y));
        if(curVel.x >= -1000.0)
            cpBodySetForce(userControlObject->body, cpv(-100000.0, 0.0));
    }
    if(keyStates[GLFW_KEY_D] || keyStates[GLFW_KEY_RIGHT])
    {
        cpVect curVel = cpBodyGetVelocity(userControlObject->body);
        if(curVel.x < 0)
            cpBodySetVelocity(userControlObject->body, cpv(0, curVel.y));
        if(curVel.x <= 1000.0)
            cpBodySetForce(userControlObject->body, cpv(100000.0, 0.0));
    }
    if(!keyStates[GLFW_KEY_A] && !keyStates[GLFW_KEY_D] && !keyStates[GLFW_KEY_LEFT] && !keyStates[GLFW_KEY_RIGHT])
    {
        cpShapeSetFriction(userControlObject->shape, 1.0f);
    }

    if(keyStates[GLFW_KEY_SPACE])
    {
        if(userControlObject->canJump)
        {
            userControlObject->jump();
            soundMap.find("Jump")->second->play();
        }

    }

    if(keyStates[GLFW_KEY_W])
    {
        camera.zoomIn();
    }

    if(keyStates[GLFW_KEY_S])
    {
        camera.zoomOut();
    }


}

void Stage::processKB(int key, int scancode, int action, int mods)
{
    if(nextEnv)
        return;

    if(action == GLFW_PRESS)
    {
        keyStates[key] = 1;
        if(key == GLFW_KEY_LEFT || key == GLFW_KEY_A || key == GLFW_KEY_RIGHT || key == GLFW_KEY_D)
            cpShapeSetFriction(userControlObject->shape, 0.0f);
    }
    else if(action == GLFW_RELEASE)
    {
        keyStates[key] = 0;
    }
}


bool Stage::processMousePosition(float xpos, float ypos)
{

    mouseX = xpos;
    mouseY = ypos;

    return false;

}



void Stage::processMouseClick(int button, int action, int mods)
{
    return;
}


/*** Step the space through time dt ***/
void Stage::updateEnvironment(double dt)
{
    if(userControlObject->dead)
    {
        nextEnv = new Stage(stageName);
        return;
    }

    if(winTimer > 0)
        winTimer--;
    else if(winTimer == 0)
    {
        nextEnv = new Menu(false);
        return;
    }
    else if(userControlObject->levelWin)
        winTimer = 250;

    cpSpaceStep(envSpace, dt);
    for(KinematicObject* ko : kinematicObjects)
        ko->update(dt);

    cpVect controlPos = cpBodyGetPosition(userControlObject->body);
    Obj::matView = glm::lookAt(glm::vec3(controlPos.x, controlPos.y + 400.0f * camera.zoom, 1000.0f * camera.zoom), glm::vec3(controlPos.x, controlPos.y, 0.0f), camera.up);


    skybox->position = glm::vec3(controlPos.x, controlPos.y, 0);

}


/*** Draw all objects/boundaries in the environment ***/
void Stage::drawEnvironment()
{
    if(nextEnv)
        return;

    /*** Draw skybox ***/
    glDepthMask(GL_FALSE);
    glFrontFace(GL_CW);
    static_cast<StandardObject*>(skybox)->render();
    glFrontFace(GL_CCW);
    glDepthMask(GL_TRUE);


    /*** Draw all dynamic objects ***/
    for(int i = 0; i < physicsObjects.size(); i++)
    {
        if(physicsObjects[i]->draw)
            physicsObjects[i]->render();
    }

    for(int i = 0; i < kinematicObjects.size(); i++)
    {
        if(kinematicObjects[i]->draw)
            kinematicObjects[i]->render();
    }

    /*** Draw all standard objects ***/
    for(int i = 0; i < standardObjects.size(); i++)
    {
        if(standardObjects[i]->draw)
            standardObjects[i]->render();
    }

    /*** Draw hero ***/
    static_cast<PhysicsObject*>(userControlObject)->render();

    static_cast<PhysicsObject*>(boundary)->render();

}


/*** Update the projection matrix ***/
void Stage::updateScreenSize()
{
    Obj::matProjection = glm::perspective(60.0f*3.1415f/180.0f, Environment::screenWidth/Environment::screenHeight, 10.0f, 30000.0f);
}


Hero* Stage::getUserControl(){
    return userControlObject;
}
