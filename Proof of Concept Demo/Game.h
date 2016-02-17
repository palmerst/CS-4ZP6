#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"
#include "Stage.h"
#include "ObjGPUData.h"
#include "MenuManager.h"
#include <map>

/*! The Game class is a representation of the game on the highest level.  It handles all exchanges between the user and the game code.  It keeps a reference to the game window as well as the current environment of the game (main menu, stage, etc) and acts as a bridge between the two.
 *  User inputs are intercepted through GLFW callbacks in this class and passed on for processing by the current game environment.
 *  This class is also responsible for "running" the game and sends requests for the game environment to be updated and drawn to the screen at regular intervals (framerate is controlled).
 */

class Game {

    GLFWwindow* window;     //!< Reference to the GLFWwindow (the window)
    Environment* env;       //!< Reference to the current Environment

//    std::map<std::string, ObjGPUData*> objMap;  //!< Data for objects that are used by the GPU (i.e. meshes/texture mappings/etc.)
//                                                //!< Stored as key/value pairs where the key is a string description for ease of tracking and accessing stored objects while coding

    double timeLast;        //!< Last time that was polled;  used for framerate control
    double timeElapsed;     //!< Time elapsed since last polling of time;  used for framerate control

    float winX;     //!< Stores x-coordinate maximum of the window
    float winY;     //!< Stores y-coordinate maximum of the window


    MenuManager *menuManager;  //!< menu manager
    bool gamePause;            //!< game will pause if opened menu
    bool soundOn;
    bool musicOn;

    public:
        Game(int, char**);         //!< Game class constructor
        ~Game();        //!< Game class destructor

        void run();     //!< Runs the game until the application is terminated (infinite loop)

        void framebuffer_size_callback(GLFWwindow*, int, int);      //!< GLFW window resize callback
        void key_callback(GLFWwindow*, int, int, int, int);         //!< GLFW keyboard input callback
        void mouse_pos_callback(GLFWwindow*, float, float);         //!< GLFW mouse position change callback
        void mouse_button_callback(GLFWwindow*, int, int, int);     //!< GLFW mouse button input callback

        //!< MenuManager to Game class interface
        void PauseGame();   //!< pause game
        void ContinueGame();//!< unpause game

        void SoundSetting();
        void MusicSetting();
        bool IsSoundOn() { return soundOn; }
        bool IsMusciOn() { return musicOn; }
};

#endif // GAME_H_INCLUDED
