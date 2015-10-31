#include "Environment.h"
#include <iostream>

Environment::Environment(std::vector<GLuint>* VAOList){

    envSpace = cpSpaceNew();
    cpSpaceSetIterations(envSpace, 20);
	cpSpaceSetGravity(envSpace, cpv(0, -9.8));
    cpSpaceSetSleepTimeThreshold(envSpace, 5.0f);

    glGenVertexArrays(1, &staticVAO);
    glGenBuffers(1, &staticVBO);

    glBindVertexArray(staticVAO);

    glBindBuffer(GL_ARRAY_BUFFER, staticVBO);
    glBufferData(GL_ARRAY_BUFFER, staticMasterVertexList.size() * sizeof(glm::vec3), &staticMasterVertexList[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );

    glBindVertexArray(0);

    masterObjectVAOList = VAOList;

    shader = loadShaders("vert.glsl", "frag.glsl");

	MVP_ID = glGetUniformLocation(shader, "MVP");

	mat_Projection = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f);
}


void Environment::updateStaticObjectBufferData(){

    glBindVertexArray(staticVAO);

    glBindBuffer(GL_ARRAY_BUFFER, staticVBO);
    glBufferData(GL_ARRAY_BUFFER, staticMasterVertexList.size() * sizeof(glm::vec3), &staticMasterVertexList[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );

    glBindVertexArray(0);

}

void Environment::addStaticObject(cpVect p1, cpVect p2, Static_Obj_Type staticType){

    if(staticType == STATIC_BOUNDARY)
        staticObjects.push_back(new Boundary(envSpace, staticMasterVertexList, p1, p2));

    updateStaticObjectBufferData();

}

void Environment::addDynamicObject(glm::vec2 pos, Dynamic_Obj_Type dynamicType){

    if(dynamicType == DYNAMIC_CHARACTER)
        dynamicObjects.push_back(new Character(envSpace, pos));

}

void Environment::updateEnvironment(){

    cpSpaceStep(envSpace, 0.001);

}

void Environment::drawEnvironment(){

    glm::mat4 MVP = glm::mat4(1.0f);

    glUseProgram(shader);

    glBindVertexArray(staticVAO);
    MVP = mat_Projection;
    glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, &MVP[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, staticMasterVertexList.size());
    glBindVertexArray(0);

    for(int i = 0; i < dynamicObjects.size(); i++){
        glBindVertexArray((*masterObjectVAOList)[0]);
        cpVect pos = cpBodyGetPosition(dynamicObjects[i]->body);
        float angle = cpBodyGetAngle(dynamicObjects[i]->body);
        MVP = mat_Projection * glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0.0f)) * glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0, 1));
        glUniformMatrix4fv(MVP_ID, 1, GL_FALSE, &MVP[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

}

void Environment::updateProjection(glm::mat4 newProjection){
    mat_Projection = newProjection;
}
