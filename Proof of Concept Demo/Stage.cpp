#include "Stage.h"

Stage::Stage(int count, char** argv){

    /*** Set up space variables ***/
    envSpace = cpSpaceNew();
    cpSpaceSetIterations(envSpace, 10);
	cpSpaceSetGravity(envSpace, cpv(0, -1500));
	PhysicsObject::space = envSpace;
  //  cpSpaceSetSleepTimeThreshold(envSpace, 5.0f);


    /*** Load the shaders and store handle ***/



//    shaderProgram = loadShaders("objectVertex.glsl", "objectFragment.glsl");
//
//    /*** Associate identifiers with locations in shader ***/
//	MVP_ID = glGetUniformLocation(shaderProgram, "MVP");
//    MV_ID = glGetUniformLocation(shaderProgram, "ModelViewMatrix");
//    M_ID = glGetUniformLocation(shaderProgram, "ModelMatrix");
//    P_ID = glGetUniformLocation(shaderProgram, "ProjectionMatrix");
//    N_ID = glGetUniformLocation(shaderProgram, "NormalMatrix");
//    MTL_KA_ID = glGetUniformLocation(shaderProgram, "Material.Ka");
//    MTL_KD_ID = glGetUniformLocation(shaderProgram, "Material.Kd");
//    MTL_KS_ID = glGetUniformLocation(shaderProgram, "Material.Ks");
//    MTL_SHINE_ID = glGetUniformLocation(shaderProgram, "Material.shine");
//    LPOS_ID = glGetUniformLocation(shaderProgram, "Light.Position");
//    LA_ID = glGetUniformLocation(shaderProgram, "Light.La");
//    LD_ID = glGetUniformLocation(shaderProgram, "Light.Ld");
//    LS_ID = glGetUniformLocation(shaderProgram, "Light.Ls");
//    texture_ID = glGetUniformLocation(shaderProgram, "myTextureSampler");
//    subroutine_object = glGetSubroutineIndex(shaderProgram, GL_VERTEX_SHADER, "object");
//    subroutine_boundary_xy = glGetSubroutineIndex(shaderProgram, GL_VERTEX_SHADER, "boundary_xy");
//    subroutine_boundary_yz = glGetSubroutineIndex(shaderProgram, GL_VERTEX_SHADER, "boundary_yz");
//    subroutine_boundary_xz = glGetSubroutineIndex(shaderProgram, GL_VERTEX_SHADER, "boundary_xz");

    /*** Set up projection and view matrices -- these numbers will probably change ***/
	mat_Projection = glm::perspective(60.0f*3.1415f/180.0f, 1.0f, 10.0f, 3000.0f);
	Obj::matProjection = mat_Projection;
	//mat_Projection = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, 10.0f, 300.0f);


    setCollisionHandlers(envSpace);

    /** STAGE DESIGN GOES BELOW HERE **/

	physicsObjects.push_back(new Platform(-1500, 1500, 1525));
	physicsObjects.push_back(new Platform(-1450, 1450, -975));
	physicsObjects.push_back(new Platform(150, 700, 25));
	physicsObjects.push_back(new Platform(-1450, -1050, -675));
	physicsObjects.push_back(new Platform(-750, -400, -525));
	physicsObjects.push_back(new Platform(-400, -100, -125));
	physicsObjects.push_back(new Platform(-1450, -400, 375));
	physicsObjects.push_back(new Platform(-700, 1450, 825));

	physicsObjects.push_back(new Wall(-1000, 1500, -1475));
	physicsObjects.push_back(new Wall(-1000, 1500, 1475));
	physicsObjects.push_back(new Wall(-500, -100, -425));

    userControlObject = new Hero(-770, 800);

    /** STAGE DESIGN GOES ABOVE HERE **/

    mat_View = glm::lookAt(glm::vec3(0.0f, 500.0f, 2000.0f), glm::vec3(-770.0f, 800.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    soundMap.insert(std::pair<std::string, Sound*>("Background", new Sound("./data/sound/bm.wav", 1)));
    soundMap.insert(std::pair<std::string, Sound*>("Bullet", new Sound("./data/sound/bullet.wav", 0)));
    soundMap.insert(std::pair<std::string, Sound*>("Jump", new Sound("./data/sound/jump.wav", 0)));

    soundMap.find("Background")->second->play();                     //play bgm
}

//clean
Stage::~Stage()
{

}

void Stage::processContinuousInput(){

    if(keyStates[GLFW_KEY_A])
    {
        cpVect curVel = cpBodyGetVelocity(userControlObject->body);
        if(curVel.x <= -1000.0)
            return;
        cpBodySetForce(userControlObject->body, cpv(-100000.0, 0.0));
        return;
    }
    if(keyStates[GLFW_KEY_D])
    {
        cpVect curVel = cpBodyGetVelocity(userControlObject->body);
        if(curVel.x >= 1000.0)
            return;
        cpBodySetForce(userControlObject->body, cpv(100000.0, 0.0));
        return;
    }
    if(!keyStates[GLFW_KEY_A] && !keyStates[GLFW_KEY_D])
    {
        cpVect curVel = cpBodyGetVelocity(userControlObject->body);
        if(curVel.x == 0)
            return;
        else
        {
            curVel.x /= 1.1;
            if(curVel.x > -100 || curVel.x < 100)
                curVel.x = 0;
            cpBodySetVelocity(userControlObject->body, curVel);
        }
    }

}

void Stage::processKB(int key, int scancode, int action, int mods)
{
    switch(key){
    case GLFW_KEY_A:
        {
            if(action == GLFW_PRESS)
                keyStates[GLFW_KEY_A] = 1;
            else if(action == GLFW_RELEASE)
                keyStates[GLFW_KEY_A] = 0;
            break;
        }
    case GLFW_KEY_D:
        {
            if(action == GLFW_PRESS)
                keyStates[GLFW_KEY_D] = 1;
            else if(action == GLFW_RELEASE)
                keyStates[GLFW_KEY_D] = 0;
            break;
        }
    case GLFW_KEY_SPACE:
        {
            cpVect curVel = cpBodyGetVelocity(userControlObject->body);
            if(curVel.y < 0.01 && curVel.y > -0.01){
                cpBodySetVelocity(userControlObject->body, cpvadd(curVel, cpv(0.0, 1150.0)));
                soundMap.find("Jump")->second->play();
            }
            break;
        }
    default:
        break;
    }

}


void Stage::processMousePosition(float xpos, float ypos){
    mouseX = xpos;
    mouseY = ypos;
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
    mat_View = glm::lookAt(glm::vec3(controlPos.x, controlPos.y + 500.0f, 2000.0f), glm::vec3(controlPos.x, controlPos.y, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Obj::matView = mat_View;

}


/*** Draw all objects/boundaries in the environment ***/
void Stage::drawEnvironment(){


    /*** Draw all dynamic objects ***/
    for(int i = 0; i < physicsObjects.size(); i++){

        if(physicsObjects[i]->draw)
            physicsObjects[i]->render();

    }

    /*** Draw hero ***/
    userControlObject->render();

}


/*** Update the projection matrix ***/
void Environment::updateProjection(glm::mat4 newProjection){
    mat_Projection = newProjection;
}