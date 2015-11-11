#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"
#include "Environment.h"
#include "ObjGPUData.h"
#include <map>

/*** Handles all inputs/outputs between the game code and the window ***/

class Game {

    GLFWwindow* window;
    Environment* game;

    /*** Map of object gpu data (keys = string descriptions) ***/
    std::map<std::string, ObjGPUData*> objMap;

    double timeLast;

    public:
        Game();

        /*** Run the game until application is terminated ***/
        void run();

        /*** Resize callback ***/
        void framebuffer_size_callback(GLFWwindow*, int, int);

};

#endif // GAME_H_INCLUDED
