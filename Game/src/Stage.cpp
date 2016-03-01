#include "Stage.h"

#include <iostream>

Stage::Stage(std::string stageName){

    /*** Set up space variables ***/
    envSpace = cpSpaceNew();
    cpSpaceSetIterations(envSpace, 10);
	cpSpaceSetGravity(envSpace, cpv(0, -1500));
	PhysicsObject::space = envSpace;
  //  cpSpaceSetSleepTimeThreshold(envSpace, 5.0f);


    /*** Set up projection and view matrices -- these numbers will probably change ***/
	Obj::matProjection = glm::perspective(60.0f*3.1415f/180.0f, 1.0f, 10.0f, 18000.0f);
	//mat_Projection = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, 10.0f, 300.0f);

    overlay = 0;
    nextEnv = 0;

    setCollisionHandlers(envSpace);

    /** STAGE DESIGN GOES BELOW HERE **/

	physicsObjects.push_back(new Platform(-1500, 1500, 1525));
	physicsObjects.push_back(new Platform(-1450, 1450, -975));
	physicsObjects.push_back(new Platform(150, 700, 25));


	physicsObjects.push_back(new Platform(-1450, -400, 375));
	physicsObjects.push_back(new Spikes(-1200, -25, 3.141592f));
	physicsObjects.push_back(new Platform(-700, 1450, 825));

	physicsObjects.push_back(new Wall(-200, 1500, -1475));
	physicsObjects.push_back(new Ramp(1450, 4500, -975, 500));

	physicsObjects.push_back(new Boulder(4200, 900));
	physicsObjects.push_back(new Spears(-1750, -950));
    physicsObjects.push_back(new Spikes(-800, -950));

    physicsObjects.push_back(new Platform(-500, -200, -300));

    standardObjects.push_back(new Arch(3800, -975));

	boundary = new Boundary(-30000, 30000, -975, BS_SAND);
    userControlObject = new Hero(-770, 800);
    skybox = new Skybox(0, 0, 1);

    /** STAGE DESIGN GOES ABOVE HERE **/

    mat_View = glm::lookAt(glm::vec3(0.0f, 500.0f, 2000.0f), glm::vec3(-770.0f, 800.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    soundMap.insert(std::pair<std::string, Sound*>("Background", new Sound("./data/sound/bm.wav")));
    soundMap.insert(std::pair<std::string, Sound*>("Jump", new Sound("./data/sound/jump.wav")));

    soundMap.find("Background")->second->play(1);                     //play bgm
}

//clean
Stage::~Stage()
{

}

void Stage::processContinuousInput(){

    if(keyStates[GLFW_KEY_A])
    {
        cpVect curVel = cpBodyGetVelocity(userControlObject->body);
        if(curVel.x >= -1000.0)
            cpBodySetForce(userControlObject->body, cpv(-100000.0, 0.0));
    }
    if(keyStates[GLFW_KEY_D])
    {
        cpVect curVel = cpBodyGetVelocity(userControlObject->body);
        if(curVel.x <= 1000.0)
            cpBodySetForce(userControlObject->body, cpv(100000.0, 0.0));
    }
    if(!keyStates[GLFW_KEY_A] && !keyStates[GLFW_KEY_D])
    {
        cpVect curVel = cpBodyGetVelocity(userControlObject->body);
        if(curVel.x != 0)
        {
            curVel.x /= 1.1;
            if(curVel.x > -100 || curVel.x < 100)
                curVel.x = 0;
            cpBodySetVelocity(userControlObject->body, curVel);
        }
    }

    if(keyStates[GLFW_KEY_SPACE]){
        cpVect curVel = cpBodyGetVelocity(userControlObject->body);
        //            if(curVel.y < 0.5 && curVel.y > -0.5){
        //                cpBodySetVelocity(userControlObject->body, cpvadd(curVel, cpv(0.0, 1150.0)));
        //                soundMap.find("Jump")->second->play();
        //            }
        if(userControlObject->canJump){
            cpBodySetVelocity(userControlObject->body, cpvadd(curVel, cpv(0.0, 1150.0)));
            soundMap.find("Jump")->second->play();
        }

    }

    if(keyStates[GLFW_KEY_E]){
        firstPerson = !firstPerson;
        camera = Camera();
        keyStates[GLFW_KEY_E] = 0;
    }

    if(keyStates[GLFW_KEY_P]){
        nextEnv = new Stage(std::string());
        keyStates[GLFW_KEY_P] = 0;
    }

}

void Stage::processKB(int key, int scancode, int action, int mods)
{

    if(action == GLFW_PRESS)
        keyStates[key] = 1;
    else if(action == GLFW_RELEASE)
        keyStates[key] = 0;

}


bool Stage::processMousePosition(float xpos, float ypos, float winX, float winY){

    if(firstPerson){
        camera.moveOrigin((float)(ypos - mouseY)/500.0f, (float)(xpos - mouseX)/500.0f);
    }

    mouseX = xpos;
    mouseY = ypos;

    return false;

}



void Stage::processMouseClick(int button, int action, int mods, float winX, float winY){
//    winX -= 1;
//    winY -= 1;
//
//    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
//        cpVect controlPos = cpBodyGetPosition(userControlObject->body);
//        cpVect mousePos = cpv(mouseX - winX/2, mouseY - winY/2);
//        cpVect bulletVel = cpvmult(cpvnormalize(mousePos),225.0);
//        cpFloat bulletAngle = cpvtoangle(mousePos) - 3.141592/2.0;
//        DynamicObject* bullet = new DynamicObject(envSpace, glm::vec2(controlPos.x, controlPos.y), 3, 3, 0.5, 1, gpuMap.find("Bullet")->second, OBJ_HERO_BULLET);
//        cpBodySetVelocity(bullet->body, bulletVel);
//        cpBodySetAngle(bullet->body, bulletAngle);
//        dynamicObjects.push_back(bullet);
//        soundMap.find("Bullet")->second->play();
//    }
}


/*** Step the space through time dt ***/
void Stage::updateEnvironment(double dt){

    cpSpaceStep(envSpace, dt);
    cpVect controlPos = cpBodyGetPosition(userControlObject->body);
    if(firstPerson){
        camera.update(glm::vec3(controlPos.x, controlPos.y + userControlObject->height/4.0f, 0.0f));
        Obj::matView = glm::lookAt(camera.pos, camera.origin, camera.up);
    } else
        Obj::matView = glm::lookAt(glm::vec3(controlPos.x, controlPos.y + 400.0f, 1000.0f), glm::vec3(controlPos.x, controlPos.y, 0.0f), camera.up);
    skybox->position = glm::vec3(controlPos.x, controlPos.y, 0);

}


/*** Draw all objects/boundaries in the environment ***/
void Stage::drawEnvironment(){

    /*** Draw skybox ***/
    glDepthMask(GL_FALSE);
    glFrontFace(GL_CW);
    static_cast<StandardObject*>(skybox)->render();
    glFrontFace(GL_CCW);
    glDepthMask(GL_TRUE);


    /*** Draw all dynamic objects ***/
    for(int i = 0; i < physicsObjects.size(); i++){

        if(physicsObjects[i]->draw)
            physicsObjects[i]->render();

    }

    /*** Draw all standard objects ***/
    for(int i = 0; i < standardObjects.size(); i++){

        if(standardObjects[i]->draw)
            standardObjects[i]->render();
    }

    /*** Draw hero ***/
    static_cast<PhysicsObject*>(userControlObject)->render();

    static_cast<PhysicsObject*>(boundary)->render();

}


/*** Update the projection matrix ***/
void Environment::updateProjection(glm::mat4 newProjection){
    Obj::matProjection = newProjection;
}
