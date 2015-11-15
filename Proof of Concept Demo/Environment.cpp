
#include "Environment.h"
#include "Loader.h"
#include "gameInput.h"

#include <stdio.h>
#include <iostream>

Environment::Environment(){

    /*** Set up space variables ***/
    envSpace = cpSpaceNew();
    cpSpaceSetIterations(envSpace, 10);
	cpSpaceSetGravity(envSpace, cpv(0, -100));
    cpSpaceSetSleepTimeThreshold(envSpace, 5.0f);

    /*** Load the shaders and store handle ***/
    shaderProgram = loadShaders("objectVertex.glsl", "objectFragment.glsl");

    /*** Associate identifiers with locations in shader ***/
	MVP_ID = glGetUniformLocation(shaderProgram, "MVP");
    MV_ID = glGetUniformLocation(shaderProgram, "ModelViewMatrix");
    M_ID = glGetUniformLocation(shaderProgram, "ModelMatrix");
    P_ID = glGetUniformLocation(shaderProgram, "ProjectionMatrix");
    N_ID = glGetUniformLocation(shaderProgram, "NormalMatrix");
    MTL_KA_ID = glGetUniformLocation(shaderProgram, "Material.Ka");
    MTL_KD_ID = glGetUniformLocation(shaderProgram, "Material.Kd");
    MTL_KS_ID = glGetUniformLocation(shaderProgram, "Material.Ks");
    MTL_SHINE_ID = glGetUniformLocation(shaderProgram, "Material.shine");
    LPOS_ID = glGetUniformLocation(shaderProgram, "Light.Position");
    LA_ID = glGetUniformLocation(shaderProgram, "Light.La");
    LD_ID = glGetUniformLocation(shaderProgram, "Light.Ld");
    LS_ID = glGetUniformLocation(shaderProgram, "Light.Ls");
    texture_ID = glGetUniformLocation(shaderProgram, "myTextureSampler");
    subroutine_object = glGetSubroutineIndex(shaderProgram, GL_VERTEX_SHADER, "object");
    subroutine_boundary_xy = glGetSubroutineIndex(shaderProgram, GL_VERTEX_SHADER, "boundary_xy");
    subroutine_boundary_yz = glGetSubroutineIndex(shaderProgram, GL_VERTEX_SHADER, "boundary_yz");
    subroutine_boundary_xz = glGetSubroutineIndex(shaderProgram, GL_VERTEX_SHADER, "boundary_xz");

    /*** Set up projection and view matrices -- these numbers will probably change ***/
	mat_Projection = glm::perspective(60.0f*3.1415f/180.0f, 1.0f, 10.0f, 300.0f);
	//mat_Projection = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, 10.0f, 300.0f);
	mat_View = glm::lookAt(glm::vec3(0.0f, 50.0f, 200.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    gpuData = new ObjGPUData("./data/testchar", 3.1415f);
	role = new RoleObject(envSpace,glm::vec2(-100,120),gpuData);    //initial character

	snd_initialize();       //initial sound
    m_bm = snd_new("bm.wav",1);         //load bgm
    m_sound = snd_new("sound.wav",0);   //load sound

    snd_play(m_bm);                     //play bgm
}

//clean
Environment::~Environment()
{
    delete role;
    delete gpuData;

    size_t cnt = bullets.size();
    for(size_t idx=0;idx<cnt;idx++)
        delete bullets[idx];
    bullets.clear();

    snd_free(m_sound);
    snd_free(m_bm);
    snd_cleanup();
}

//test only see the input respond
static void test_input_module(uint op)
{
    if(op&INPUT_OP_UP)
        printf("up repeat!\n");
    if(op&INPUT_OP_UP_START)
        printf("up pressed!\n");
    if(op&INPUT_OP_UP_STOP)
        printf("up released!\n");

    if(op&INPUT_OP_LEFT)
        printf("left repeat!\n");
    if(op&INPUT_OP_LEFT_START)
        printf("left pressed!\n");
    if(op&INPUT_OP_LEFT_STOP)
        printf("left released!\n");

    if(op&INPUT_OP_RIGHT)
        printf("right repeat!\n");
    if(op&INPUT_OP_RIGHT_START)
        printf("right pressed!\n");
    if(op&INPUT_OP_RIGHT_STOP)
        printf("right released!\n");

    if(op&INPUT_OP_DOWN)
        printf("down repeat!\n");
    if(op&INPUT_OP_DOWN_START)
        printf("down pressed!\n");
    if(op&INPUT_OP_DOWN_STOP)
        printf("down released!\n");

    if(op&INPUT_OP_A)
        printf("button A repeat!\n");
    if(op&INPUT_OP_A_START)
        printf("button A pressed!\n");
    if(op&INPUT_OP_A_STOP)
        printf("button A released!\n");

    if(op&INPUT_OP_B)
        printf("button B repeat!\n");
    if(op&INPUT_OP_B_START)
        printf("button B pressed!\n");
    if(op&INPUT_OP_B_STOP)
        printf("button B released!\n");

    if(op&INPUT_OP_C)
        printf("button C repeat!\n");
    if(op&INPUT_OP_C_START)
        printf("button C pressed!\n");
    if(op&INPUT_OP_C_STOP)
        printf("button C released!\n");

    if(op&INPUT_OP_D)
        printf("button D repeat!\n");
    if(op&INPUT_OP_D_START)
        printf("button D pressed!\n");
    if(op&INPUT_OP_D_STOP)
        printf("button D released!\n");
}

void Environment::processUserInput(unsigned int operation)
{
    //test_input_module(operation);

    if(operation&INPUT_OP_RIGHT_START || operation&INPUT_OP_RIGHT)  //right movement
    {
        printf("right pressed!\n");

        cpVect curVec = cpBodyGetVelocity(role->body);
        if(curVec.x >= 100.0)   //max speed
            curVec.x = 100.0;
        else
        {   //x velocity
            role->mAcceleration = cpv(20.0,0.0);
            curVec.x += role->mAcceleration.x;
            //curVec.y += role->mAcceleration.y;
        }
        cpBodySetVelocity(role->body,curVec);
        role->dir = 1;//bullet direction
    }
    else if(operation&INPUT_OP_LEFT_START || operation&INPUT_OP_LEFT){   //left movement
        printf("left pressed\!n");
        printf("left pressed£¡\n");

        cpVect curVec = cpBodyGetVelocity(role->body);
        if(curVec.x <= -100.0)
            curVec.x = -100.0;
        else
        {
            role->mAcceleration = cpv(-20.0,0.0);
            curVec.x += role->mAcceleration.x;
            //curVec.y += role->mAcceleration.y;
        }

        cpBodySetVelocity(role->body,curVec);
        role->dir = 2;
    }
    else
    {   //de acceleration
        cpVect curVec = cpBodyGetVelocity(role->body);
        if(role->dir==1)
        {

            if(curVec.x <= 0.0)
                curVec.x = 0.0;
            else
            {
                role->mAcceleration = cpv(-10.0,0.0);
                curVec.x += role->mAcceleration.x;
                //curVec.y += role->mAcceleration.y;
            }
        }
        else if(role->dir == 2)
        {
            if(curVec.x>= 0.0)
                curVec.x = 0.0;
            else
            {
                role->mAcceleration = cpv(10.0,0.0);
                curVec.x += role->mAcceleration.x;
                //curVec.y += role->mAcceleration.y;
            }
        }

        cpBodySetVelocity(role->body,curVec);
    }

    //press c(j) to shot
    if(operation&INPUT_OP_C_START || operation&INPUT_OP_C)
    {
        cpVect pos,velocity;        //bullet position
        pos = cpBodyGetPosition(role->body);
        if(role->dir == 1)      //base on main character, it will determine bullet direction
        {
            pos.x += 11.0;
            velocity = cpv(350.0,0.0);  //bullet speed
        }
        else if(role->dir==2)
        {
            pos.x -= 11.0;
            velocity = cpv(-350.0,0.0);
        }
        BulletObjet *tmp = new BulletObjet(envSpace,glm::vec2(pos.x,pos.y),gpuData);
        cpBodySetVelocity(tmp->body,velocity);
        bullets.push_back(tmp);
        snd_play(m_sound);      //play sound
    }

}

/*** Adds a box boundary from p1 (lower left) to p2 (upper right) ***
 *** Links to gpu data representing the boundary visuals          ***/
void Environment::addBoundary(cpVect p1, cpVect p2, ObjGPUData* gpuData){

    boundaries.push_back(Boundary(envSpace, p1, p2, gpuData));

}

/*** Adds a dynamic object with centroid at position pos and links to gpu data ***/
void Environment::addDynamicObject(glm::vec2 pos, ObjGPUData* gpuData){

    dynamicObjects.push_back(DynamicObject(envSpace, pos, gpuData));

}

/*** Step the space through time dt ***/
void Environment::updateEnvironment(double dt){

    cpSpaceStep(envSpace, dt);

}


/*** Draw all objects/boundaries in the environment ***/
void Environment::drawEnvironment(){

    /***  Bind the shader program ***/
    glUseProgram(shaderProgram);

    /*** Draw all dynamic objects ***/
    for(int i = 0; i < dynamicObjects.size(); i++){

        drawObj(dynamicObjects[i]);

    }

    /*** Draw all boundaries ***/
    for(int i = 0; i < boundaries.size(); i++){

        drawObj(boundaries[i], true);

    }
    //draw main character
    drawObj(*role);

    size_t cnt = bullets.size();
    for(size_t idx=0;idx<cnt;idx++)
        drawObj(*bullets[idx]);

    /***  Unbind shaders and VAO ***/
    glBindVertexArray(0);
    glUseProgram(0);
}

/*** Draw an object ***/
void Environment::drawObj(Obj currentObj, bool isBoundary){

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
        glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &subroutine_object);
    }

    /*** Bind VAO associated w/ object ***/
    glBindVertexArray(currentGPUObj->vertexArrayObj);

    /*** Iterate through all of the object pieces and render ***/
    int cnt = currentGPUObj->materialIndices.size() / 2;
    for(int i = 0; i < cnt; i++){

        unsigned int first = (currentGPUObj->materialIndices)[i*2];
        unsigned int last;

        if((2*i + 2) > (cnt - 1))
            last = currentGPUObj->fList.size();
        else
            last = (currentGPUObj->materialIndices)[i*2 + 2];

        unsigned int totalElements = last - first;

        /***  Bind the textures required by the object piece ***/
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, (currentGPUObj->materials)[(currentGPUObj->materialIndices)[i*2 + 1]].texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glUniform1i(currentGPUObj->texture_ID, 0);

        /***  Calculate transformations used in rendering the object piece and pass to shaders ***/
        glm::mat4 modelMat = glm::translate(glm::mat4(1.0f),
                    glm::vec3(pos.x, pos.y, 0.0f)) * glm::rotate(glm::mat4(1.0f),
                    angle,
                    glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), modelScale) * currentGPUObj->rotation * currentGPUObj->unitScale;
        glm::mat4 modelViewMat = mat_View*modelMat;
        glm::mat4 MVP = mat_Projection*modelViewMat;
//            glm::mat3 normalMat = glm::transpose(glm::inverse(glm::mat3(modelViewMat)));
        glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, &MVP[0][0]);
//            glUniformMatrix4fv(MV_ID, 1, GL_FALSE, &modelViewMat[0][0]);
//            glUniformMatrix4fv(P_ID, 1, GL_FALSE, &mat_Projection[0][0]);
//            glUniformMatrix3fv(N_ID, 1, GL_FALSE, &normalMat[0][0]);
        glUniformMatrix4fv(M_ID, 1, GL_FALSE, &modelMat[0][0]);
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

        /*** Call subroutines for boundaries (texture is applied differently -- tiled for boundaries) ***/
        if(isBoundary){
            switch(i){
            case 0:
                glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &subroutine_boundary_yz);
                break;
            case 1:
                glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &subroutine_boundary_xy);
                break;
            case 2:
                glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &subroutine_boundary_yz);
                break;
            case 3:
                glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &subroutine_boundary_xz);
                break;
            }
        }

        /*** Render the object piece ***/
        glDrawElements(GL_TRIANGLES, totalElements, GL_UNSIGNED_INT, (void*)(first * sizeof(GLuint)));
    }

}


/*** Update the projection matrix ***/
void Environment::updateProjection(glm::mat4 newProjection){
    mat_Projection = newProjection;
}
