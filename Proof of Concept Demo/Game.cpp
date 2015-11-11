#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"
#include <cstdio>
#include <cstdlib>

#include "Game.h"
#include "ObjGPUData.h"

Game::Game(){

    /*** Initialize the library ***/
    if (!glfwInit())
        exit(1);

    /*** Use multisampling ***/
    glfwWindowHint(GLFW_SAMPLES, 4);

    /*** Create a windowed mode window and its OpenGL context ***/
    window = glfwCreateWindow(600, 600, "Untitled Game", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(2);
    }

    /*** Make the window's context current ***/
    glfwMakeContextCurrent(window);

    /*** Initialize glew ***/
    glewExperimental = true;
	GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(3);
	}

    /*** Enable depth testing for 3d rendering ***/
	glEnable(GL_DEPTH_TEST);

    /*** Register member function callbacks ***/
    glfwSetWindowUserPointer(window, this);

    auto wfunc = [](GLFWwindow* w, int width, int height)
    {
        static_cast<Game*>(glfwGetWindowUserPointer(w))->framebuffer_size_callback(w, width, height);
    };

    glfwSetFramebufferSizeCallback(window, wfunc);


    /*** Associate an environment with the game ***/
    game = new Environment();

    /*** Populate the environment                                   ***
     *** This code will eventually be moved -- here is fine for PoC ***/
    objMap.insert(std::pair<std::string, ObjGPUData*>("Hero", new ObjGPUData("./data/testchar", 3.1415f)));
    objMap.insert(std::pair<std::string, ObjGPUData*>("Boundary", new ObjGPUData("./data/testbound")));

    game->addBoundary(cpv(-150,-100), cpv(-145,100), objMap.find("Boundary")->second);
	game->addBoundary(cpv(-145,-100), cpv(145, -95), objMap.find("Boundary")->second);
	game->addBoundary(cpv(145,-100), cpv(150,100), objMap.find("Boundary")->second);
	game->addBoundary(cpv(15,0), cpv(70,5), objMap.find("Boundary")->second);
	game->addBoundary(cpv(-55,-55), cpv(-10,-50), objMap.find("Boundary")->second);
	game->addDynamicObject(glm::vec2(-77,80), objMap.find("Hero")->second);
	game->addDynamicObject(glm::vec2(0,-30), objMap.find("Hero")->second);
	game->addDynamicObject(glm::vec2(-44,55), objMap.find("Hero")->second);
	game->addDynamicObject(glm::vec2(24,80), objMap.find("Hero")->second);
	game->addDynamicObject(glm::vec2(44,50), objMap.find("Hero")->second);
	game->addDynamicObject(glm::vec2(90,80), objMap.find("Hero")->second);

    /*** Set time to current ***/
    timeLast = glfwGetTime();
}


/*** Run game until terminated ***/
void Game::run(){

    while (!glfwWindowShouldClose(window))
    {
        /*** Clear depth and color buffers ***/
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        /*** Update environment through elapsed time step and draw ***/
        double timeCurrent = glfwGetTime();
        game->updateEnvironment(timeCurrent - timeLast);
        game->drawEnvironment();
        timeLast = timeCurrent;

        /*** Swap buffers ***/
        glfwSwapBuffers(window);

        /*** Poll for and process events ***/
        glfwPollEvents();
    }

    glfwTerminate();
}

/*** Resize window callback ***/
void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    game->updateProjection(glm::perspective(60.0f*3.1415f/180.0f, (float)width/(float)height, 10.0f, 300.0f));
}

