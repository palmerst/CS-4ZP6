#ifndef MENU_MANAGER_H_INCLUDED
#define MENU_MANAGER_H_INCLUDED

#include<vector>

//!< menu call back function declare 
typedef void (*MenuItemHandler)(void* pParam);

class Game;

typedef struct _MenuItem
{
    int xPos,yPos,index;  //!< menu position
    int width,height;     //!< menu width and hight
    float x,y;

    //!< menu call back function
    MenuItemHandler handler;
    void* pParam;

    //!<different picture will be use if menu state is different
    unsigned char *imgNormal;
    unsigned char *imgHover;
    unsigned char *imgClicked;
    unsigned char *imgCurrent;

    short level;
    bool active;
    bool posFixed;
    bool clicked;

    void* user_data;
}MenuItem;

class MenuManager
{
public:
    MenuManager();
    ~MenuManager();

    bool intialize(Game* game,int width,int height);
    void cleanup();

    void newScreenSize(int width,int height);   //!<¡¡will be use when windows size changed

    //!< add new menu item
    void addNewItem(char* szNormal,char* szHover,char* szSelected,
                    int posX,int posY,
                    MenuItemHandler handler,void *param,
                    short level,
                    bool active=false,bool fixed=false);

    //!< mouse movement in game windows
    void processMouseMove(float x,float y);

    //!< mouse click in game windows
    void processMouseClicked(int button,int action);

    void drawMenuItems();               //!< draw menu
    void ShowSubMenu(int level,bool bShow=true);  //!< show submenu
    //void ShowSettings();

private:
    std::vector<MenuItem*> vecMenuItem; //!< save all menu

    Game *theGame;
    float screenWidth,screenHeight;     //!< screen hight and width use this to set menu

    float mouseX,mouseY;                //!< record mouse position


    void hover_menuitem(MenuItem*);     //!< use this function when mouse move
    void click_menuitem(MenuItem*);     //!< use this function when mouse click
};


#endif // MENU_MANAGER_H_INCLUDED
