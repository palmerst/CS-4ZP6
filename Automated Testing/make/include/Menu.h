#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <vector>
#include "Environment.h"

//!< menu function
typedef void (*MenuItemHandler)(void* pParam);

typedef struct _MenuItem
{
    int xPos,yPos,index;  //!< menu location
    int width,height;     //!< menu high and width
    float x,y;

    //!< menu handler
    MenuItemHandler handler;
    void* pParam;

    //!<picture data
    unsigned char *imgNormal;
    unsigned char *imgHover;
    unsigned char *imgClicked;
    unsigned char *imgCurrent;

    short level;
    bool active;        //!< activiton state
    bool posFixed;      //!< position
    bool clicked;       //!< mouse click

    void* user_data;
}MenuItem;


/*! The Menu class is derived from the Environment class and holds and handles changes to the game state when the user is not playing a stage (i.e. is in a menu of some kind).
 */
class Menu : public Environment
{

private:
    std::vector<MenuItem*> vecMenuItem; //!< Stores menu buttons.

    void hover_menuitem(MenuItem*);     //!< Called when mouse position is changes to detect hover over buttons.
    void click_menuitem(MenuItem*);     //!< Called when mouse is clicked to detect click on buttons.

public:

    Menu(bool inGame);     //!< Menu constructor.
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
    bool processMousePosition(float xpos, float ypos);

    //! Function for mouse input processing.
    /*!
      \param button Mouse button to which the action corresponds.
      \param action The action (i.e. button up, down, held, etc.)
      \param mods Active modifiers (i.e. shift, control, etc.)
    */
    void processMouseClick(int button, int action, int mods);

    //! Displays main menu.
    /*!
      \param level Menu depth.
      \param bShow Flag specifies whether buttons should be drawn.
    */
    void ShowSubMenu(int level,bool bShow=true);

    //! Displays level select menu.
    /*!
      \param bShow Flag specifies whether buttons should be drawn.
    */
    void showLevelSubMenu(bool bShow);

    //! Changes layout due to screen size update.
    void updateScreenSize();

    //! Adds button to the menu.
    void addNewItem(char* szNormal,char* szHover,char* szSelected,
                    int posX,int posY,
                    MenuItemHandler handler,void *param,
                    short level,
                    bool active=false,bool fixed=false);
};

#endif // MENU_MANAGER_H_INCLUDED
