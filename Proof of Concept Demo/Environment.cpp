#include "Environment.h"
#include "Loader.h"
#include "Shader.h"

#include <stdio.h>
#include <iostream>
#include <string>

Stage::Stage(int count, char** argv){

    /*** Set up space variables ***/
    envSpace = cpSpaceNew();
    cpSpaceSetIterations(envSpace, 10);
	cpSpaceSetGravity(envSpace, cpv(0, -150));
  //  cpSpaceSetSleepTimeThreshold(envSpace, 5.0f);


    /*** Load the shaders and store handle ***/

    shaderMap.insert(std::pair<std::string, Shader*>("BoundaryXY", new Shader("vBoundaryXY.glsl", "fUniversal.glsl")));
    shaderMap.insert(std::pair<std::string, Shader*>("BoundaryXZ", new Shader("vBoundaryXZ.glsl", "fUniversal.glsl")));
    shaderMap.insert(std::pair<std::string, Shader*>("BoundaryYZ", new Shader("vBoundaryYZ.glsl", "fUniversal.glsl")));
    shaderMap.insert(std::pair<std::string, Shader*>("Object", new Shader("vObject.glsl", "fUniversal.glsl")));


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
	mat_Projection = glm::perspective(60.0f*3.1415f/180.0f, 1.0f, 10.0f, 300.0f);
	//mat_Projection = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, 10.0f, 300.0f);


    setCollisionHandlers(envSpace);

    gpuMap.insert(std::pair<std::string, ObjGPUData*>("Hero", new ObjGPUData("./data/obj/testchar", 3.1415f)));
    gpuMap.insert(std::pair<std::string, ObjGPUData*>("Enemy", new ObjGPUData("./data/obj/testenemy", 3.1415f)));
    gpuMap.insert(std::pair<std::string, ObjGPUData*>("Boundary", new ObjGPUData("./data/obj/testbound")));
    gpuMap.insert(std::pair<std::string, ObjGPUData*>("Bullet", new ObjGPUData("./data/obj/bullet")));

    addBoundary(cpv(-150,150), cpv(150, 155), gpuMap.find("Boundary")->second);
    addBoundary(cpv(-150,-100), cpv(-145,150), gpuMap.find("Boundary")->second);
	addBoundary(cpv(-145,-100), cpv(145, -95), gpuMap.find("Boundary")->second);
	addBoundary(cpv(145,-100), cpv(150,150), gpuMap.find("Boundary")->second);
	addBoundary(cpv(15,0), cpv(70,5), gpuMap.find("Boundary")->second);
	addBoundary(cpv(-145, -70), cpv(-105, -65), gpuMap.find("Boundary")->second);
	addBoundary(cpv(-75,-55), cpv(-40,-50), gpuMap.find("Boundary")->second);
	addBoundary(cpv(-45,-50), cpv(-40,-10), gpuMap.find("Boundary")->second);
	addBoundary(cpv(-40,-15), cpv(-10,-10), gpuMap.find("Boundary")->second);
	addBoundary(cpv(-145,35), cpv(-40, 40), gpuMap.find("Boundary")->second);
	addBoundary(cpv(-70,80), cpv(145, 85), gpuMap.find("Boundary")->second);

    dynamicObjects.push_back(new DynamicObject(envSpace, glm::vec2(0,-30), 100, 20, 0.5, 1, gpuMap.find("Enemy")->second, OBJ_ENEMY, true));
	dynamicObjects.push_back(new DynamicObject(envSpace, glm::vec2(-44,55), 100, 20, 0.5, 1, gpuMap.find("Enemy")->second, OBJ_ENEMY, true));
	dynamicObjects.push_back(new DynamicObject(envSpace, glm::vec2(24,80), 100, 20, 0.5, 1, gpuMap.find("Enemy")->second, OBJ_ENEMY, true));
	dynamicObjects.push_back(new DynamicObject(envSpace, glm::vec2(-130,-50), 100, 20, 0.5, 1, gpuMap.find("Enemy")->second, OBJ_ENEMY, true));
	dynamicObjects.push_back(new DynamicObject(envSpace, glm::vec2(90,80), 100, 20, 0.5, 1, gpuMap.find("Enemy")->second, OBJ_ENEMY, true));
    dynamicObjects.push_back(new DynamicObject(envSpace, glm::vec2(90,130), 100, 20, 0.5, 1, gpuMap.find("Enemy")->second, OBJ_ENEMY, true));
	dynamicObjects.push_back(new DynamicObject(envSpace, glm::vec2(0,130), 100, 20, 0.5, 1, gpuMap.find("Enemy")->second, OBJ_ENEMY, true));
	dynamicObjects.push_back(new DynamicObject(envSpace, glm::vec2(-120,80), 100, 20, 0.5, 1, gpuMap.find("Enemy")->second, OBJ_ENEMY, true));


    userControlObject = new DynamicObject(envSpace, glm::vec2(-77,80), 100, 20, 0, 0, gpuMap.find("Hero")->second, OBJ_HERO, true);

    mat_View = glm::lookAt(glm::vec3(0.0f, 50.0f, 200.0f), glm::vec3(-77.0f, 80.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

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
        if(curVel.x <= -100.0)
            return;
        cpBodySetForce(userControlObject->body, cpv(-30000.0, 0.0));
        return;
    }
    if(keyStates[GLFW_KEY_D])
    {
        cpVect curVel = cpBodyGetVelocity(userControlObject->body);
        if(curVel.x >= 100.0)
            return;
        cpBodySetForce(userControlObject->body, cpv(30000.0, 0.0));
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
            if(curVel.x > -10 || curVel.x < 10)
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
            if(curVel.y < 0.001 && curVel.y > -0.001){
                cpBodySetVelocity(userControlObject->body, cpvadd(curVel, cpv(0.0, 115.0)));
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
    winX -= 1;
    winY -= 1;

    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        cpVect controlPos = cpBodyGetPosition(userControlObject->body);
        cpVect mousePos = cpv(mouseX - winX/2, mouseY - winY/2);
        cpVect bulletVel = cpvmult(cpvnormalize(mousePos),225.0);
        cpFloat bulletAngle = cpvtoangle(mousePos) - 3.141592/2.0;
        DynamicObject* bullet = new DynamicObject(envSpace, glm::vec2(controlPos.x, controlPos.y), 3, 3, 0.5, 1, gpuMap.find("Bullet")->second, OBJ_HERO_BULLET);
        cpBodySetVelocity(bullet->body, bulletVel);
        cpBodySetAngle(bullet->body, bulletAngle);
        dynamicObjects.push_back(bullet);
        soundMap.find("Bullet")->second->play();
    }
}

/*** Adds a box boundary from p1 (lower left) to p2 (upper right) ***
 *** Links to gpu data representing the boundary visuals          ***/
void Stage::addBoundary(cpVect p1, cpVect p2, ObjGPUData* gpuData){

    boundaries.push_back(new StaticObject(envSpace, p1, p2, gpuData));

}

/*** Step the space through time dt ***/
void Stage::updateEnvironment(double dt){

    cpSpaceStep(envSpace, dt);
    cpVect controlPos = cpBodyGetPosition(userControlObject->body);
    mat_View = glm::lookAt(glm::vec3(controlPos.x, controlPos.y + 50.0f, 200.0f), glm::vec3(controlPos.x, controlPos.y, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

}


/*** Draw all objects/boundaries in the environment ***/
void Stage::drawEnvironment(){

    /***  Bind the object shader program ***/
    Shader* nextShader;
    nextShader = shaderMap.find("Object")->second;
    changeShader(nextShader);
    glUseProgram(nextShader->shaderProgram);

    /*** Draw all dynamic objects ***/
    for(int i = 0; i < dynamicObjects.size(); i++){

        if(dynamicObjects[i]->draw)
            drawObj(*dynamicObjects[i]);

    }

    /*** Draw hero ***/
    drawObj(*userControlObject);

    /*** Draw all boundaries ***/
    for(int i = 0; i < boundaries.size(); i++){

        if(boundaries[i]->draw)
            drawObj(*boundaries[i], true);

    }

    /***  Unbind shaders and VAO ***/
    glBindVertexArray(0);
    glUseProgram(0);
}

/*** Draw an object ***/
void Stage::drawObj(Obj currentObj, bool isBoundary){

    ObjGPUData* currentGPUObj = currentObj.gpuData;

    /*** Get current position and angle of the object ***/
    cpVect pos = cpBodyGetPosition(currentObj.body);
    float angle = cpBodyGetAngle(currentObj.body);

    glm::vec3 modelScale;

    /*** Scale the model appropriately:  if boundary, scale to the width and height of the boundary                        ***
     ***                                 if object, scale all axis to height (objects are scaled to height 1.0 when loaded ***/
    if(isBoundary){
        modelScale = glm::vec3(currentObj.width, currentObj.height, 50.0f);
    } else {
        modelScale = glm::vec3(currentObj.height);
    }

    /*** Bind VAO associated w/ object ***/
    glBindVertexArray(currentGPUObj->vertexArrayObj);

    /*** Iterate through all of the object pieces and render ***/
    for(int i = 0; i < currentGPUObj->materialIndices.size()/2; i++){

        if(isBoundary){
            Shader* nextShader;
            switch(i){
                case 0:
                    nextShader = shaderMap.find("BoundaryYZ")->second;
                    break;
                case 1:
                    nextShader = shaderMap.find("BoundaryXY")->second;
                    break;
                case 2:
                    nextShader = shaderMap.find("BoundaryYZ")->second;
                    break;
                case 3:
                    nextShader = shaderMap.find("BoundaryXZ")->second;
                    break;
                case 4:
                    nextShader = shaderMap.find("BoundaryXZ")->second;
                    break;
            }
            changeShader(nextShader);
        }

        unsigned int first = (currentGPUObj->materialIndices)[i*2];
        unsigned int last;

        if((2*i + 2) > (currentGPUObj->materialIndices.size() - 1))
            last = currentGPUObj->fList.size();
        else
            last = (currentGPUObj->materialIndices)[i*2 + 2];

        unsigned int totalElements = last - first;

        /***  Bind the textures required by the object piece ***/
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, (currentGPUObj->materials)[(currentGPUObj->materialIndices)[i*2 + 1]].texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glUniform1i(currentShader->uniformIDMap.find("myTextureSampler")->second, 0);

        /***  Calculate transformations used in rendering the object piece and pass to shaders ***/
        glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0.0f)) * glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), modelScale) * currentGPUObj->rotation * currentGPUObj->unitScale;
        glm::mat4 modelViewMat = mat_View*modelMat;
        glm::mat4 MVP = mat_Projection*modelViewMat;
//            glm::mat3 normalMat = glm::transpose(glm::inverse(glm::mat3(modelViewMat)));
        glUniformMatrix4fv(currentShader->uniformIDMap.find("MVP")->second, 1, GL_FALSE, &MVP[0][0]);
//            glUniformMatrix4fv(MV_ID, 1, GL_FALSE, &modelViewMat[0][0]);
//            glUniformMatrix4fv(P_ID, 1, GL_FALSE, &mat_Projection[0][0]);
//            glUniformMatrix3fv(N_ID, 1, GL_FALSE, &normalMat[0][0]);
        glUniformMatrix4fv(currentShader->uniformIDMap.find("ModelMatrix")->second, 1, GL_FALSE, &modelMat[0][0]);
//
//            //  Pass material info to shaders
//            glUniform3fv(currentGPUObj->MTL_KA_ID, 1, &((currentGPUObj->materials)[(currentGPUObj->materialIndices)[i*2 + 1]].Ka)[0]);
//            glUniform3fv(currentGPUObj->MTL_KD_ID, 1, &((currentGPUObj->materials)[(currentGPUObj->materialIndices)[i*2 + 1]].Kd)[0]);
//            glUniform3fv(currentGPUObj->MTL_KS_ID, 1, &((currentGPUObj->materials)[(currentGPUObj->materialIndices)[i*2 + 1]].Ks)[0]);
//            glUniform1f(currentGPUObj->MTL_SHINE_ID, (currentGPUObj->materials)[(currentGPUObj->materialIndices)[i*2 + 1]].shine);

        //  Pass light info to shaders
//            glm::vec4 sunLightPos_ViewSpace = viewMat * sunLightPos;    //  Transform sun position to view space
//            glUniform4fv(obj->LPOS_ID, 1, &sunLightPos_ViewSpace[0]);
//            glUniform3fv(obj->LA_ID, 1, &sunLightLa[0]);
//            glUniform3fv(obj->LD_ID, 1, &sunLightLd[0]);
//            glUniform3fv(obj->LS_ID, 1, &sunLightLs[0]);


        /*** Render the object piece ***/
        glDrawElements(GL_TRIANGLES, totalElements, GL_UNSIGNED_INT, (void*)(first * sizeof(GLuint)));
    }

}


/*** Update the projection matrix ***/
void Environment::updateProjection(glm::mat4 newProjection){
    mat_Projection = newProjection;
}


void Environment::changeShader(Shader* nextShader){
    if(currentShader != nextShader){
        glUseProgram(nextShader->shaderProgram);
        currentShader = nextShader;
    }
}
