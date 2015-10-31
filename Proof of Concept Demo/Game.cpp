#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"
#include <cstdio>
#include <cstdlib>

#include "Game.h"

Game::Game(){

    /* Initialize the library */
    if (!glfwInit())
        exit(1);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(600, 600, "Untitled Game", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(2);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewExperimental = true;
	GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(3);
	}

    glfwSetWindowUserPointer(window, this);

    auto func = [](GLFWwindow* w, int width, int height)
    {
        static_cast<Game*>(glfwGetWindowUserPointer(w))->framebuffer_size_callback(w, width, height);
    };


    glfwSetFramebufferSizeCallback(window, func);

    vertexList character;
    character.push_back(glm::vec3(-5,10,0));
    character.push_back(glm::vec3(-5,-10,0));
    character.push_back(glm::vec3(5,-10,0));
    character.push_back(glm::vec3(-5,10,0));
    character.push_back(glm::vec3(5,-10,0));
    character.push_back(glm::vec3(5,10,0));
    masterObjectVertexList.push_back(character);

    masterObjectVAOList.push_back(0);
    masterObjectVBOList.push_back(0);
    glGenVertexArrays(1, &masterObjectVAOList[0]);
    glGenBuffers(1, &masterObjectVBOList[0]);

    glBindVertexArray(masterObjectVAOList[0]);

    glBindBuffer(GL_ARRAY_BUFFER, masterObjectVBOList[0]);
    glBufferData(GL_ARRAY_BUFFER, masterObjectVertexList[0].size() * sizeof(glm::vec3), &masterObjectVertexList[0][0], GL_STATIC_DRAW);
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

    game = new Environment(&masterObjectVAOList);

    game->addStaticObject(cpv(-100,-100), cpv(-95,100), STATIC_BOUNDARY);
	game->addStaticObject(cpv(-95,-100), cpv(95, -95), STATIC_BOUNDARY);
	game->addStaticObject(cpv(95,-100), cpv(100,100), STATIC_BOUNDARY);
	game->addDynamicObject(glm::vec2(-77,80), DYNAMIC_CHARACTER);
	game->addDynamicObject(glm::vec2(0,-30), DYNAMIC_CHARACTER);
	game->addDynamicObject(glm::vec2(-44,55), DYNAMIC_CHARACTER);
	game->addDynamicObject(glm::vec2(24,80), DYNAMIC_CHARACTER);
	game->addDynamicObject(glm::vec2(44,50), DYNAMIC_CHARACTER);
	game->addDynamicObject(glm::vec2(90,80), DYNAMIC_CHARACTER);

}


void Game::run(){
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        game->updateEnvironment();
        game->drawEnvironment();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}


void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    float wProj, hProj;
    if(width <= height){
        wProj = 100.0;
        hProj = 100.0*((float)height/(float)width);
    } else {
        hProj = 100.0;
        wProj = 100.0*((float)width/(float)height);
    }

    game->updateProjection(glm::ortho(-wProj, wProj, -hProj, hProj));
}
