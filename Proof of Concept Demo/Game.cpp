#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"
#include "include/AL/alut.h"
#include <cstdio>
#include <cstdlib>

#include "Game.h"
#include "ObjGPUData.h"


Game::Game(int count, char** argv){

    /*** Initialize glfw ***/
    if (!glfwInit())
    {
        printf("Failed to initialize GLFW");
        exit(1);
    }

    /*** Use multisampling ***/
    glfwWindowHint(GLFW_SAMPLES, 4);

    /*** Create a windowed mode window and its OpenGL context ***/
    window = glfwCreateWindow(600, 600, "Untitled Game", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(2);
    }

    winX = 600;
    winY = 600;

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

    
	//!<make menu control group
    menuManager = new MenuManager();
    menuManager->intialize(this,winX,winY);
    gamePause = false;
    soundOn = true;
    musicOn = true;

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


    /*** Associate an environment with the game ***/
    env = new Stage(count, argv);


    /*** Set time to current ***/
    timeLast = glfwGetTime();
    timeElapsed = 0;
}

Game::~Game()
{
    menuManager->cleanup();
    delete menuManager;
}


/*** Run game until terminated ***/
void Game::run(){

    while (!glfwWindowShouldClose(window))
    {
        /*** Update environment through elapsed time step and draw ***/
        double timeCurrent = glfwGetTime();
        timeElapsed += timeCurrent - timeLast;
        timeLast = timeCurrent;

        if(timeElapsed >= 0.01667){
            timeElapsed = 0;
            glfwSwapBuffers(window);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            if(gamePause==false)        //!<base on the game state decide update game contant or not
            {
                env->processContinuousInput();
                env->updateEnvironment(0.01667);
            }
            env->drawEnvironment();
            menuManager->drawMenuItems();       //!<update menu
            timeCurrent = glfwGetTime();
            timeElapsed += timeCurrent - timeLast;
            timeLast = timeCurrent;
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

    env->updateProjection(glm::perspective(60.0f*3.1415f/180.0f, (float)width/(float)height, 10.0f, 18000.0f));
    menuManager->newScreenSize(width,height);

    winX = width;
    winY = height;
}


/*** Keyboard callback ***/
void Game::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    env->processKB(key, scancode, action, mods);
}

void Game::mouse_pos_callback(GLFWwindow* window, float xpos, float ypos)
{
    menuManager->processMouseMove(xpos,ypos);               //!< mouse move
    env->processMousePosition(xpos, winY - ypos - 1);
}

void Game::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    menuManager->processMouseClicked(button,action);        //!< mouse click

    env->processMouseClick(button, action, mods, winX, winY);

}

void Game::PauseGame()
{
    gamePause = true;
}

void Game::ContinueGame()
{
    gamePause = false;
}

void Game::SoundSetting()
{
    soundOn = !soundOn;
    if(soundOn==true)   //!< open sound
    {
        //!< todo
        env->soundMusicControl(1,true);
    }
    else                //!< close sound
    {
        //!< todo
        env->soundMusicControl(1,false);
    }
}

void Game::MusicSetting()
{
    musicOn = !musicOn;
    if(musicOn==true)       //!< open music
    {
        //!< todo
        env->soundMusicControl(2,true);
    }
    else                    //!< close music
    {
        //!< todo
        env->soundMusicControl(2,false);
    }
}
