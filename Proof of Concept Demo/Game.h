#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"
#include "Environment.h"

class Game {

    GLFWwindow* window;
    Environment* game;

    std::vector<vertexList> masterObjectVertexList;
    std::vector<GLuint> masterObjectVAOList;
    std::vector<GLuint> masterObjectVBOList;


    public:
        Game();
        void run();
        void framebuffer_size_callback(GLFWwindow*, int, int);

};

#endif // GAME_H_INCLUDED
