#ifndef STAGE_H_INCLUDED
#define STAGE_H_INCLUDED

#include "Environment.h"
#include "Camera.h"

/*! The Stage class is derived from the Environment class and holds and handles changes to the game state when the user is playing a stage.
 */
class Stage : public Environment
{

private:

    cpSpace* envSpace;      //!< Pointer to the chipmunk space associated with the stage.

    /*** Objects in environment ***/
    std::vector<PhysicsObject*> physicsObjects;
    std::vector<KinematicObject*> kinematicObjects;
    std::vector<StandardObject*> standardObjects;

    Skybox* skybox;
    Boundary* boundary;

    float stageTime;     //!< Time elapsed since beginning the stage.


    //! Draws an object.
    /*!
      \param currentObj Object that should be drawn.
      \param isBoundary Flag for boundaries (default = false);  boundaries are drawn slightly differently.
    */
    void drawObj(PhysicsObject currentObj, bool isBoundary = false);

    /*** Controlled object ***/
    Hero* userControlObject;    //!< Pointer to the dynamic object that is controlled by the user (normally the hero object).

    bool firstPerson = false;

    Camera camera;

public:


    Stage(std::string stageName);  //!< Stage constructor.

    ~Stage();  //!< Stage destructor.

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
    bool processMousePosition(float xpos, float ypos, float winX, float winY);

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

#endif // STAGE_H_INCLUDED
