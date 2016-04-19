#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "AL/alut.h"
#include <cstdio>
#include <cstdlib>

#include "Game.h"
#include "Stage.h"
#include "Menu.h"

Game::Game(int count, char** argv)
{

    /*** Initialize glfw ***/
    if (!glfwInit())
    {
        printf("Failed to initialize GLFW");
        exit(1);
    }

    /*** Use multisampling ***/
    glfwWindowHint(GLFW_SAMPLES, 4);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /*** Create a windowed mode window and its OpenGL context ***/
    window = glfwCreateWindow(1800, 1200, "Platform Perils", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(2);
    }

    winX = 1800;
    winY = 1200;

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

    /*** Initialize OpenAL ***/
    int OPENAL_OK = 1;

    alutInit(0,NULL);

    // Clear the error code.
    alGetError();

    //source setting
    ALfloat listenerPosition[] = {0.0f, 0.0f, 0.0f};
    ALfloat listenerVelocity[] = {0.0f, 0.0f, 0.0f};
    ALfloat listenerOrientation[] = {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f};

    alListenerfv(AL_POSITION,listenerPosition);
    if (alGetError()!=AL_NO_ERROR)
        OPENAL_OK = 0;

    alListenerfv(AL_VELOCITY,listenerVelocity);
    if (alGetError()!=AL_NO_ERROR)
        OPENAL_OK = 0;

    alListenerfv(AL_ORIENTATION,listenerOrientation);
    if (alGetError()!=AL_NO_ERROR)
        OPENAL_OK = 0;

    if(!OPENAL_OK)
    {
        printf("Failed to initialize OpenAL");
        exit(4);
    }

    /*** Enable depth testing for 3d rendering ***/
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(1.0, 1.0, 1.0, 1.0);

    /*** Register member function callbacks ***/
    glfwSetWindowUserPointer(window, this);

    auto wfunc = [](GLFWwindow* w, int width, int height)
    {
        static_cast<Game*>(glfwGetWindowUserPointer(w))->framebuffer_size_callback(w, width, height);
    };

    auto kbfunc = [](GLFWwindow* w, int key, int scancode, int action, int mods)
    {
        static_cast<Game*>(glfwGetWindowUserPointer(w))->key_callback(w, key, scancode, action, mods);
    };

    auto mposfunc = [](GLFWwindow* w, double xpos, double ypos)
    {
        static_cast<Game*>(glfwGetWindowUserPointer(w))->mouse_pos_callback(w, xpos, ypos);
    };

    auto mbutfunc = [](GLFWwindow* w, int button, int action, int mods)
    {
        static_cast<Game*>(glfwGetWindowUserPointer(w))->mouse_button_callback(w, button, action, mods);
    };

    glfwSetFramebufferSizeCallback(window, wfunc);
    glfwSetKeyCallback(window, kbfunc);
    glfwSetCursorPosCallback(window, mposfunc);
    glfwSetMouseButtonCallback(window, mbutfunc);

  //  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    /*** Associate an environment with the game ***/
   // env = new Stage(std::string());
//   Environment::screenHeight = 1000;
//   Environment::screenWidth = 1800;
    env = new Menu(false);

    glfwSetWindowSize(window, 1800, 1000);

    /*** Set time to current ***/
    timeLast = glfwGetTime();
    timeElapsed = 0;
}

Game::~Game()
{

}


/*** Run game until terminated ***/
void Game::run()
{

    double frameMin = 1.0/60.0;

    while (!glfwWindowShouldClose(window))
    {
        /*** Update environment through elapsed time step and draw ***/
        double timeCurrent = glfwGetTime();
        timeElapsed += timeCurrent - timeLast;
        timeLast = timeCurrent;

        if(timeElapsed >= frameMin)
        {
            Environment* curEnv = env;
            while(curEnv){
                if(curEnv->nextEnv)
                {
                    Environment* temp = curEnv->nextEnv;
                    delete env;
                    env = temp;
                }

                curEnv = curEnv->overlay;
            }


            timeElapsed = 0;
            glfwSwapBuffers(window);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            env->processContinuousInput();
            env->updateEnvironment(frameMin);
            env->drawEnvironment();
            Environment* overlay = env->overlay;
            while(overlay){
                overlay->processContinuousInput();
                overlay->updateEnvironment(frameMin);
                overlay->drawEnvironment();
                overlay = overlay->overlay;
            }
//            timeCurrent = glfwGetTime();
//            timeElapsed += timeCurrent - timeLast;
//            timeLast = timeCurrent;

        }


        /*** Poll for and process events ***/
        glfwPollEvents();
    }


    glfwTerminate();
}

/*** Resize window callback ***/
void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    Environment::screenWidth = width;
    Environment::screenHeight = height;

    env->updateScreenSize();
    Environment* overlay = env->overlay;
    while(overlay){
        overlay->updateScreenSize();
        overlay = overlay->overlay;
    }
}


/*** Keyboard callback ***/
void Game::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE)
        exit(0);
    env->processKB(key, scancode, action, mods);
    Environment* overlay = env->overlay;
    while(overlay){
        overlay->processKB(key, scancode, action, mods);
        overlay = overlay->overlay;
    }
}

void Game::mouse_pos_callback(GLFWwindow* window, float xpos, float ypos)
{
    env->processMousePosition(xpos, ypos);
    Environment* overlay = env->overlay;
    while(overlay){
        overlay->processMousePosition(xpos, ypos);
        overlay = overlay->overlay;
    }
}

void Game::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    env->processMouseClick(button, action, mods);
    Environment* overlay = env->overlay;
    while(overlay){
        overlay->processMouseClick(button, action, mods);
        overlay = overlay->overlay;
    }
}
