#include "Menu.h"
#include "GL/glew.h"
#include "Obj.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Stage.h"


//load bitmap's raw date
#define BITMAPFILEHEADER_SIZE 14
#define BMPRAWDATA_OFFSET     10
typedef unsigned int    dword;
typedef int             mLong;
typedef unsigned short  word;
typedef struct tagMyBITMAPINFOHEADER
{
    dword      biSize;
    mLong      biWidth;
    mLong      biHeight;
    word       biPlanes;
    word       biBitCount;
    dword      biCompression;
    dword      biSizeImage;
    mLong      biXPelsPerMeter;
    mLong      biYPelsPerMeter;
    dword      biClrUsed;
    dword      biClrImportant;
} MyBITMAPINFOHEADER;

//load date from bmp
static unsigned char* load_bmpdata(const char *bmp_path,int *nWidth, int *nHeight)
{
    MyBITMAPINFOHEADER bmp_info = {0};
    FILE          *file_bmp;
    unsigned char *bmp_data;
    unsigned char bmp_header[BITMAPFILEHEADER_SIZE];
    size_t        read_size;
    size_t        data_size;

    file_bmp = fopen(bmp_path, "rb");
    if (file_bmp == NULL)
        return NULL;

    fread(bmp_header, BITMAPFILEHEADER_SIZE, 1, file_bmp);
    fread(&bmp_info, sizeof(MyBITMAPINFOHEADER), 1, file_bmp);
    fseek(file_bmp, (long)*((dword*)(bmp_header+BMPRAWDATA_OFFSET)), SEEK_SET);
    *nWidth = bmp_info.biWidth;
    *nHeight = bmp_info.biHeight;
    data_size = bmp_info.biSizeImage;

    if(data_size == 0)
        data_size = 4 * *nWidth  * abs(*nHeight);

    bmp_data = (unsigned char*)malloc(data_size);
    if (!bmp_data)
    {
        free(bmp_data);
        fclose(file_bmp);
        return NULL;
    }

    read_size = fread(bmp_data, 1, data_size, file_bmp);
    if ( read_size == 0 )
    {
        free(bmp_data);
        fclose(file_bmp);
        return NULL;
    }

    fclose(file_bmp);

    return bmp_data;
}

//!< s_theGame is represent game class able to use gamne function in menu event handler
//!< control game stream
//static Game *s_theGame;

static unsigned char* s_bkImg = NULL;
static int s_bkImgWdith = 0;
static int s_bkImgHeight = 0;


void MenuMainHandler(void* pParam)
{
    Menu *mgr = (Menu*)pParam;
    mgr->nextEnv = new Menu(false);
}

void MenuSettingHandler(void* pParam)
{
    Menu *mgr = (Menu*)pParam;
    mgr->ShowSubMenu(2,true);
}

void MenuNewgameHandler(void* pParam)
{
    Menu *mgr = (Menu*)pParam;
}

void MenuLevSelectHandler(void* pParam)
{
    Menu *mgr = (Menu*)pParam;
    mgr->showLevelSubMenu(true);
}

void MenuContinueHandler(void* pParam)
{
    Menu *mgr = (Menu*)pParam;
    mgr->ShowSubMenu(1,false);

    // s_theGame->GameStart();
    if(s_bkImg!=NULL)
    {
        free(s_bkImg);
        s_bkImg = NULL;
    }
}

void MenuQuitHandler(void* pParam)
{
    exit(0);
}

void MenuMusicHandler(void* pParam)
{
    MenuItem *item = (MenuItem*) pParam;
//    Game* theGame = (Game*)item->user_data;

    char szMusiconNormal[] = "./data/menu/musicon_normal.bmp";
    char szMusiconClicked[] = "./data/menu/musicon_clicked.bmp";
    char szMusicoffNormal[] = "./data/menu/musicoff_normal.bmp";
    char szMusicoffClicked[] = "./data/menu/musicoff_clicked.bmp";
    char *szNormal,*szClicked;
    int w,h;
//    if(theGame->IsMusciOn())
//    {
//        szNormal = szMusicoffNormal;
//        szClicked = szMusicoffClicked;
//    }
//    else
//    {
//        szNormal = szMusiconNormal;
//        szClicked = szMusiconClicked;
//    }

    free(item->imgNormal);
    free(item->imgHover);
    free(item->imgClicked);
    item->imgNormal = load_bmpdata(szNormal,&w,&h);
    item->imgHover  = load_bmpdata(szNormal,&w,&h);
    item->imgClicked = load_bmpdata(szClicked,&w,&h);

    //theGame->MusicSetting();
}

void MenuSoundHandler(void* pParam)
{
    MenuItem *item = (MenuItem*) pParam;
//    Game* theGame = (Game*)item->user_data;

    char szSoundonNormal[] = "./data/menu/soundon_normal.bmp";
    char szSoundonClicked[] = "./data/menu/soundon_clicked.bmp";
    char szSoundoffNormal[] = "./data/menu/soundoff_normal.bmp";
    char szSoundoffClicked[] = "./data/menu/soundoff_clicked.bmp";
    char *szNormal,*szClicked;
    int w,h;
//    if(theGame->IsSoundOn())
//    {
//        szNormal = szSoundoffNormal;
//        szClicked = szSoundoffClicked;
//    }
//    else
//    {
//        szNormal = szSoundonNormal;
//        szClicked = szSoundonClicked;
//    }

    free(item->imgNormal);
    free(item->imgHover);
    free(item->imgClicked);
    item->imgNormal = load_bmpdata(szNormal,&w,&h);
    item->imgHover  = load_bmpdata(szNormal,&w,&h);
    item->imgClicked = load_bmpdata(szClicked,&w,&h);

    // theGame->SoundSetting();
}

void MenuBackHandler(void* pParam)
{
    Menu *mgr = (Menu*)pParam;
    mgr->ShowSubMenu(2,false);
}

//!< <menu>event handler for level one
void MenuLevel1Handler(void* pParam)
{
    Menu *mgr = (Menu*)pParam;
    mgr->nextEnv = new Stage("./data/stage/st1.stage");
}

//!< <menu>event handler for level two
void MenuLevel2Handler(void* pParam)
{
    Menu *mgr = (Menu*)pParam;
    mgr->nextEnv = new Stage("./data/stage/st2.stage");
}

//!< <menu>level three
void MenuLevel3Handler(void* pParam)
{
    Menu *mgr = (Menu*)pParam;
    mgr->nextEnv = new Stage("./data/stage/st3.stage");
}

void MenuLevelBackHandler(void*pParam)
{
    Menu *mgr = (Menu*)pParam;
    mgr->showLevelSubMenu(false);
}

Menu::Menu(bool inGame)
{
    nextEnv = 0;
    overlay = 0;

    char szMainNormal[] = "./data/menu/main_normal.bmp";
    char szMainClicked[] = "./data/menu/main_clicked.bmp";
    char szSettingNormal[] = "./data/menu/setting_normal.bmp";
    char szSettingClicked[] = "./data/menu/setting_clicked.bmp";
    char szNewgameNormal[] = "./data/menu/newgame_normal.bmp";
    char szNewgameClicked[] = "./data/menu/newgame_clicked.bmp";
    char szLevselectNormal[] = "./data/menu/levselect_normal.bmp";
    char szLevselectClicked[] = "./data/menu/levselect_clicked.bmp";
    char szContinueNormal[] = "./data/menu/continue_normal.bmp";
    char szContinueClicked[] = "./data/menu/continue_clicked.bmp";
    char szQuitNormal[] = "./data/menu/quit_normal.bmp";
    char szQuitClicked[] = "./data/menu/quit_clicked.bmp";
    char szMusiconNormal[] = "./data/menu/musicon_normal.bmp";
    char szMusiconClicked[] = "./data/menu/musicon_clicked.bmp";
    char szSoundonNormal[] = "./data/menu/soundon_normal.bmp";
    char szSoundonClicked[] = "./data/menu/soundon_clicked.bmp";
    char szBackNormal[] = "./data/menu/back_normal.bmp";
    char szBackClicked[] = "./data/menu/back_clicked.bmp";

    char szLevel1Normal[] = "./data/menu/level1_normal.bmp";
    char szLevel1Clicked[] = "./data/menu/level1_clicked.bmp";
    char szLevel2Normal[] = "./data/menu/level2_normal.bmp";
    char szLevel2Clicked[] = "./data/menu/level2_clicked.bmp";
    char szLevel3Normal[] = "./data/menu/level3_normal.bmp";
    char szLevel3Clicked[] = "./data/menu/level3_clicked.bmp";

    char szBg[] = "./data/menu/menu_bk.bmp";

    s_bkImg = load_bmpdata(szBg,&s_bkImgWdith,&s_bkImgHeight);

    addNewItem(szMainNormal,szMainNormal,szMainClicked,10,2,MenuMainHandler,this,0,false,true);
//   addNewItem(szSettingNormal,szSettingNormal,szSettingClicked,120,2,MenuSettingHandler,this,0,false,true);
    //  addNewItem(szNewgameNormal,szNewgameNormal,szNewgameClicked,0,1,MenuNewgameHandler,this,1,true);
    addNewItem(szLevselectNormal,szLevselectNormal,szLevselectClicked,0,2,MenuLevSelectHandler,this,1,true);
    //  addNewItem(szContinueNormal,szContinueNormal,szContinueClicked,0,3,MenuContinueHandler,this,1,true);
    addNewItem(szQuitNormal,szQuitNormal,szQuitClicked,0,4,MenuQuitHandler,this,1,true);
    // addNewItem(szMusiconNormal,szMusiconNormal,szMusiconClicked,0,1,MenuMusicHandler,this,2);
    // addNewItem(szSoundonNormal,szSoundonNormal,szSoundonClicked,0,2,MenuSoundHandler,this,2);
    addNewItem(szBackNormal,szBackNormal,szBackClicked,0,3,MenuBackHandler,this,2);

    addNewItem(szLevel1Normal,szLevel1Normal,szLevel1Clicked,0,1,MenuLevel1Handler,this,3);
    addNewItem(szLevel2Normal,szLevel2Normal,szLevel2Clicked,0,2,MenuLevel2Handler,this,3);
    addNewItem(szLevel3Normal,szLevel3Normal,szLevel3Clicked,0,3,MenuLevel3Handler,this,3);
    addNewItem(szBackNormal,szBackNormal,szBackClicked,0,4,MenuLevelBackHandler,this,3);

    if(inGame)
    {
        ShowSubMenu(1,false);
        free(s_bkImg);
        s_bkImg = NULL;
    }

}

Menu::~Menu()
{
    size_t count = vecMenuItem.size();
    for(size_t idx=0; idx<count; idx++)
    {
        MenuItem *item = vecMenuItem[idx];
        free(item->imgNormal);
        free(item->imgHover);
        free(item->imgClicked);

        delete item;
    }

    vecMenuItem.clear();
}

void Menu::updateScreenSize()
{
    int oldHeight = Environment::screenHeight;
    size_t count = vecMenuItem.size();
    for(size_t idx=0; idx<count; idx++)
    {
        MenuItem *item = vecMenuItem[idx];
        if(item->posFixed==true)
            item->yPos += (Environment::screenHeight-oldHeight);
        else
        {
            int y = Environment::screenHeight / 2 + (item->index - 2) * 30;
            item->xPos = (Environment::screenWidth - item->width) / 2;
            item->yPos = Environment::screenHeight - item->height - y;
            item->x    = item->xPos;
            item->y    = y;
        }
    }
}

void Menu::addNewItem(char* szNormal,char* szHover,char* szSelected,
                      int posX,int posY,
                      MenuItemHandler handler,void *param,
                      short level,
                      bool active,bool fixed)
{
    MenuItem *item = new MenuItem;
    int width,height;

    item->imgNormal = load_bmpdata(szNormal,&width,&height);
    item->imgHover  = load_bmpdata(szHover,&width,&height);
    item->imgClicked = load_bmpdata(szSelected,&width,&height);
    item->imgCurrent = item->imgNormal;
    item->xPos = posX;
    item->x    = posX;
    item->yPos = screenHeight - height - posY;
    item->y    = posY;
    item->width = width;
    item->height = height;
    item->handler = handler;
    item->pParam = param;
    item->level = level;
    item->active = active;
    item->posFixed = fixed;
    item->clicked = false;

    if(param==(void*)-1)
    {
        item->pParam = item;
//        item->user_data = s_theGame;
    }

    if(fixed==false)
    {
        int y = screenHeight / 2 + (posY - 2) * 48;
        item->xPos = (screenWidth - width) / 2;
        item->x    = item->xPos;
        item->yPos = screenHeight - height - y;
        item->y    = y;

        item->index = posY;
    }

    vecMenuItem.push_back(item);
}

bool Menu::processMousePosition(float xpos, float ypos)
{
    mouseX = xpos;
    mouseY = ypos;

    size_t count = vecMenuItem.size();
    for(size_t idx=0; idx<count; idx++)
    {
        if(vecMenuItem[idx]->active)
            hover_menuitem(vecMenuItem[idx]);
    }

    return false;
}

void Menu::processMouseClick(int button,int action, int mods)
{
    if(button == GLFW_MOUSE_BUTTON_LEFT)
    {
        switch(action)
        {
        case GLFW_PRESS:
        case GLFW_RELEASE:
        {
            size_t count = vecMenuItem.size();
            for(size_t idx=0; idx<count; idx++)
            {
                if(vecMenuItem[idx]->active)
                    click_menuitem(vecMenuItem[idx]);
            }
        }
        break;
        default:
            break;
        }
    }
}

void Menu::hover_menuitem(MenuItem* item)
{
    if(item->x < mouseX && mouseX <(item->x + item->width) &&
            item->y < mouseY && mouseY <(item->y + item->height))
    {
        if(item->clicked==false)
            item->imgCurrent = item->imgHover;
    }
    else
    {
        if(item->clicked==true)
        {
            item->clicked = false;
            item->imgCurrent = item->imgNormal;
        }
    }
}

void Menu::click_menuitem(MenuItem* item)
{
    if(item->x < mouseX && mouseX <(item->x + item->width) &&
            item->y < mouseY && mouseY <(item->y + item->height))
    {
        if(item->clicked==false)
        {
            item->clicked = true;
            item->imgCurrent = item->imgClicked;
        }
        else
        {
            item->clicked = false;
            item->imgCurrent = item->imgNormal;
            item->handler(item->pParam);
        }
    }
}

void Menu::drawEnvironment()
{
    Obj::currentShader = 0;
    glUseProgram(0);

    //!< <menu> push opengl to stack
    glPushAttrib(GL_LIGHTING_BIT|GL_DEPTH_BUFFER_BIT|GL_TEXTURE_BIT|GL_CURRENT_BIT);
    //!< clost opengl texture light and depth test
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D( 0.0, screenWidth, 0.0, screenHeight);

    if(s_bkImg!=NULL)
    {
        glRasterPos2i(0, 0);
        glPixelZoom((GLfloat) screenWidth / (GLfloat)s_bkImgWdith, screenHeight / (GLfloat)s_bkImgHeight);     //picture rezise
        glDrawPixels(s_bkImgWdith, s_bkImgHeight, GL_RGBA, GL_UNSIGNED_BYTE, s_bkImg);
    }

    glPixelZoom(1.0f,1.0f);

    size_t count = vecMenuItem.size();
    for(size_t idx=0; idx<count; idx++)
    {
        MenuItem *item = vecMenuItem[idx];
        if(item->active)
        {
            glRasterPos2i(item->xPos,item->yPos);
            glDrawPixels(item->width,item->height,GL_RGBA,GL_UNSIGNED_BYTE,item->imgCurrent);
        }
    }
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopAttrib();
}

void Menu::ShowSubMenu(int level,bool bShow)
{
//    if(bShow==true)
//        s_theGame->PauseGame();
//    else
//        s_theGame->ContinueGame();

    size_t count = vecMenuItem.size();
    for(size_t idx=0; idx<count; idx++)
    {
        MenuItem *item = vecMenuItem[idx];
        if(item->level==0)
        {
            item->active = !bShow;
        }
        else if(item->level==level)
        {
            item->active = bShow;
        }
    }
}

void Menu::showLevelSubMenu(bool bShow)
{
    size_t count = vecMenuItem.size();
    for(size_t idx=0; idx<count; idx++)
    {
        MenuItem *item = vecMenuItem[idx];
        if(item->level==3)
        {
            item->active = bShow;
        }
        else if(item->level==1)
        {
            item->active = !bShow;
        }
    }
}


void Menu::updateEnvironment(double dt) {}

void Menu::processKB(int key, int scancode, int action, int mods) {}
void Menu::processContinuousInput() {}
