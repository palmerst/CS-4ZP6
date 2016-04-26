#ifndef STAGE_H_INCLUDED
#define STAGE_H_INCLUDED

#include "Environment.h"
#include "Camera.h"
#include "Hero.h"

/*! The Stage class is derived from the Environment class and holds and handles changes to the game state when the user is playing a stage.
 */
class Stage : public Environment
{

private:

    cpSpace* envSpace;      //!< Pointer to the chipmunk space associated with the stage.

    /*** Objects in environment ***/
    std::vector<PhysicsObject*> physicsObjects;         //!< List of physics objects (excluding kinematic) in stage.
    std::vector<KinematicObject*> kinematicObjects;     //!< List of kinematic objects in stage.
    std::vector<StandardObject*> standardObjects;       //!< List of standard objects in stage.

    Skybox* skybox;         //!< The skybox object provides the backdrop of the stage.
    Boundary* boundary;     //!< The boundary object provides the surface setting.

    float stageTime;     //!< Time elapsed since beginning the stage.


    //! Draws an object.
    /*!
      \param currentObj Object that should be drawn.
      \param isBoundary Flag for boundaries (default = false);  boundaries are drawn slightly differently.
    */
    void drawObj(PhysicsObject currentObj, bool isBoundary = false);

    /*** Controlled object ***/
    Hero* userControlObject;    //!< Pointer to the dynamic object that is controlled by the user (normally the hero object).

    Camera camera;      //!< Used to control the view.

    int winTimer;       //!< Countdown timer set when stage is won;  determines when exit to menu occurs.

    std::string stageName;  //!< Name of current stage file (used for reseting stage).

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
    bool processMousePosition(float xpos, float ypos);

    //! Function for mouse input processing.
    /*!
      \param button Mouse button to which the action corresponds.
      \param action The action (i.e. button up, down, held, etc.)
      \param mods Active modifiers (i.e. shift, control, etc.)
    */
    void processMouseClick(int button, int action, int mods);

    //! Checks if stage is complete.
    /*!
      \return True if stage is complete, else false.
    */
    bool checkCompletion();

    //! Updates the projection matrix when screen size is changed.
    void updateScreenSize();
    
    Hero* getUserControl();
};

#endif // STAGE_H_INCLUDED
