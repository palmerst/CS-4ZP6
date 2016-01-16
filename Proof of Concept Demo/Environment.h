#ifndef ENVIRONMENT_H_INCLUDED
#define ENVIRONMENT_H_INCLUDED

#include "include/GL/glew.h"
#include "include/chipmunk/chipmunk.h"
#include "include/GLFW/glfw3.h"
#include "Obj.h"
#include "ObjGPUData.h"
#include "Sound.h"
#include "Shader.h"

#include <map>

/*! The Environment class is an abstract class that holds information about the current game state and provides function calls to update and draw the game to the screen.
 *  The Stage and Menu classes are derived from this class.
 */
class Environment {

    protected:

        /*** Object data for gpu calls ***/
        std::map<std::string, ObjGPUData*> gpuMap; //!< Stored object data used by the GPU (i.e. meshes/texture mappings/etc.).

        /*** Sound objects ***/
        std::map<std::string, Sound*> soundMap;    //!< Stored sound data.

        /*** Shaders ***/
        std::map<std::string, Shader*> shaderMap;   //!< Stored shaders.

        /*** Projection and view matrices ***/
        glm::mat4 mat_Projection;               //!< Projection matrix.
        glm::mat4 mat_View;                     //!< View matrix.

        /*** Current shader ***/
        Shader* currentShader;          //!< Pointer to the shader that is currently bound.

        float mouseX;  //!< Current position of the mouse x-coordinate.
        float mouseY;  //!< Current position of the mouse y-coordinate.

    public:

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
        virtual void processMousePosition(float xpos, float ypos) = 0;

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

};


/*! The Stage class is derived from the Environment class and holds and handles changes to the game state when the user is playing a stage.
 */
class Stage : public Environment {

    private:

        cpSpace* envSpace;      //!< Pointer to the chipmunk space associated with the stage.

        /*** Objects in environment ***/
        std::vector<StaticObject*> boundaries;          //!< Stored boundary objects (these are a special subset as they are drawn using different shaders than generic objects).
        std::vector<StaticObject*> staticObjects;       //!< Stored static objects.
        std::vector<DynamicObject*> dynamicObjects;     //!< Stored dynamic objects.
        std::vector<KinematicObject*> kinematicObjects; //!< Stored kinematic objects.

        float stageTime;     //!< Time elapsed since beginning the stage.


        //! Draws an object.
        /*!
          \param currentObj Object that should be drawn.
          \param isBoundary Flag for boundaries (default = false);  boundaries are drawn slightly differently.
        */
        void drawObj(Obj currentObj, bool isBoundary = false);

        /*** Controlled object ***/
        DynamicObject* userControlObject;    //!< Pointer to the dynamic object that is controlled by the user (normally the hero object).

    public:


        Stage(int count, char** argv);  //!< Stage constructor.

        ~Stage();  //!< Stage destructor.

        //! Adds a box boundary to the stage.
        /*!
          \param p1 Lower left coordinate of boundary
          \param p2 Upper right coordinate of boundary
          \param gpuData Pointer to the ObjGPUData that contains the gpu data used for the boundary.
        */
        void addBoundary(cpVect p1, cpVect p2, ObjGPUData* gpuData);

        //! Adds a dynamic object to the stage.
        /*!
          \param pos Position of the centroid of the object
          \param gpuData Pointer to the ObjGPUData that contains the gpu data used for the object.
        */
        void addDynamicObject(glm::vec2 pos, ObjGPUData* gpuData);

        //! Function for updating the environment.
        /*!
          \param dt Time step to be used for the update (time since last update) in milliseconds.
        */
        void updateEnvironment(double dt);

        void drawEnvironment();     //!< Function for drawing the environment.

        //! Function for keyboard input processing.
        /*!
          \param key Key to which the action corresponds.
          \param scancode System specific key code.
          \param action The action (i.e. button up, down, held, etc.)
          \param mods Active modifiers (i.e. shift, control, etc.)
        */
        void processKB(int key, int scancode, int action, int mods);
        void processContinuousInput(); //!< Function for continuous input processing.

        //! Function for mouse position change processing.
        /*!
          \param xpos Mouse cursor x-position
          \param ypos Mouse cursor y-position
        */
        void processMousePosition(float xpos, float ypos);

        //! Function for mouse input processing.
        /*!
          \param button Mouse button to which the action corresponds.
          \param action The action (i.e. button up, down, held, etc.)
          \param mods Active modifiers (i.e. shift, control, etc.)
          \param winX Mouse cursor x-position
          \param winY Mouse cursor y-position
        */
        void processMouseClick(int button, int action, int mods, float winX, float winY);

        //! Function checks if stage is complete.
        /*!
          \return True if stage is complete, else false.
        */
        bool checkCompletion();


};

/*! The Menu class is derived from the Environment class and holds and handles changes to the game state when the user is not playing a stage (i.e. is in a menu of some kind).
 */
class Menu : public Environment {


    public:

        Menu();     //!< Menu constructor.
        ~Menu();    //!< Menu destructor.

        //! Function for updating the environment.
        /*!
          \param dt Time step to be used for the update (time since last update) in milliseconds.
        */
        void updateEnvironment(double dt);

        void drawEnvironment(); //!< Function for drawing the environment.

        //! Function for keyboard input processing.
        /*!
          \param key Key to which the action corresponds.
          \param scancode System specific key code.
          \param action The action (i.e. button up, down, held, etc.)
          \param mods Active modifiers (i.e. shift, control, etc.)
        */
        void processKB(int key, int scancode, int action, int mods);
        void processContinuousInput();   //!< Function for continuous input processing.

        //! Function for mouse position change processing.
        /*!
          \param xpos Mouse cursor x-position
          \param ypos Mouse cursor y-position
        */
        void processMousePosition(float xpos, float ypos);

        //! Function for mouse input processing.
        /*!
          \param button Mouse button to which the action corresponds.
          \param action The action (i.e. button up, down, held, etc.)
          \param mods Active modifiers (i.e. shift, control, etc.)
          \param winX Mouse cursor x-position
          \param winY Mouse cursor y-position
        */
        void processMouseClick(int button, int action, int mods, float winX, float winY);
};



#endif // ENVIRONMENT_H_INCLUDED
