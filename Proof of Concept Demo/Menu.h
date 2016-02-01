#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

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

#endif // MENU_H_INCLUDED
