#ifndef ENVIRONMENT_H_INCLUDED
#define ENVIRONMENT_H_INCLUDED

#include "GL/glew.h"
#include "chipmunk/chipmunk.h"
#include "GLFW/glfw3.h"
#include "IncludeObjects.h"
#include "ObjGPUData.h"
#include "Sound.h"
#include "Shader.h"

#include <map>

/*! The Environment class is an abstract class that holds information about the current game state and provides function calls to update and draw the game to the screen.
 *  The Stage and Menu classes are derived from this class.
 */
class Environment
{

protected:

    /*** Object data for gpu calls ***/
    std::map<std::string, ObjGPUData*> gpuMap; //!< Stored object data used by the GPU (i.e. meshes/texture mappings/etc.).

    /*** Sound objects ***/
    std::map<std::string, Sound*> soundMap;    //!< Stored sound data.

    /*** Shaders ***/
    std::map<std::string, Shader*> shaderMap;   //!< Stored shaders.

    /*** Projection and view matrices ***/
    glm::mat4 mat_Projection;                   //!< Projection matrix.
    glm::mat4 mat_View;                         //!< View matrix.

    /*** Current shader ***/
    Shader* currentShader;                      //!< Pointer to the shader that is currently bound.

    float mouseX;                               //!< Current position of the mouse x-coordinate.
    float mouseY;                               //!< Current position of the mouse y-coordinate.

public:

    virtual ~Environment(){}

    int keyStates[GLFW_KEY_LAST] = {0};  //!< Array that keeps track of keyboard keys currently pressed down.

    //! Pure virtual function (i.e. defined by derived classes) for updating the environment.
    /*!
      \param dt Time step to be used for the update (time since last update) in milliseconds.
    */
    virtual void updateEnvironment(double dt) = 0;

    /*** Draw all objects in the environment ***/
    virtual void drawEnvironment() = 0;  //!< Pure virtual function (i.e. defined by derived classes) for drawing the environment.

    //! Changes the shader program.
    /*!
      \param nextShader New shader to be bound.
    */
    void changeShader(Shader* nextShader);



    /*** Input handling funcs ***/

    //! Pure virtual function (i.e. defined by derived classes) for keyboard input processing.
    /*!
      \param key Key to which the action corresponds.
      \param scancode System specific key code.
      \param action The action (i.e. button up, down, held, etc.)
      \param mods Active modifiers (i.e. shift, control, etc.)
    */
    virtual void processKB(int key, int scancode, int action, int mods) = 0;
    virtual void processContinuousInput() = 0;              //!< Pure virtual function (i.e. defined by derived classes) for continuous input processing.

    //! Pure virtual function (i.e. defined by derived classes) for mouse position change processing.
    /*!
      \param xpos Mouse cursor x-position
      \param ypos Mouse cursor y-position
    */
    virtual bool processMousePosition(float xpos, float ypos, float winX, float winY) = 0;

    //! Pure virtual function (i.e. defined by derived classes) for mouse input processing.
    /*!
      \param button Mouse button to which the action corresponds.
      \param action The action (i.e. button up, down, held, etc.)
      \param mods Active modifiers (i.e. shift, control, etc.)
      \param winX Mouse cursor x-position
      \param winY Mouse cursor y-position
    */
    virtual void processMouseClick(int button, int action, int mods, float winX, float winY) = 0;

    //! Updates the projection matrix.
    /*!
      \param newProjection New matrix to replace previous.
    */
    void updateProjection(glm::mat4 newProjection);


    Environment* overlay;           //!< Environment to overlay the current environment (in-game menu).
    Environment* nextEnv;           //!< Next environment (if non-null takes effect on next frame).

};



#endif // ENVIRONMENT_H_INCLUDED
