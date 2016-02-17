
#include "MenuManager.h"
#include "include/GL/glew.h"
#include "Obj.h"
#include "Game.h"
#include <stdio.h>
#include <stdlib.h>


//load bitmap's raw date
//my code used on 3GC3
#define BITMAPFILEHEADER_SIZE 14
#define BMPRAWDATA_OFFSET     10
typedef unsigned int    dword;
typedef int             mLong;
typedef unsigned short  word;
typedef struct tagMyBITMAPINFOHEADER{
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

MenuManager::MenuManager()
{
    screenWidth = 0;
    screenHeight = 0;
}

MenuManager::~MenuManager()
{}

void MenuMainHandler(void* pParam)
{
    MenuManager *mgr = (MenuManager*)pParam;
    mgr->ShowSubMenu(1,true);
}

void MenuSettingHandler(void* pParam)
{
    MenuManager *mgr = (MenuManager*)pParam;
    mgr->ShowSubMenu(2,true);
}

void MenuNewgameHandler(void* pParam)
{

}

void MenuLevSelectHandler(void* pParam)
{

}

void MenuContinueHandler(void* pParam)
{
    MenuManager *mgr = (MenuManager*)pParam;
    mgr->ShowSubMenu(1,false);
}

void MenuQuitHandler(void* pParam)
{
    exit(0);
}

void MenuMusicHandler(void* pParam)
{
    MenuItem *item = (MenuItem*) pParam;
    Game* theGame = (Game*)item->user_data;

    char szMusiconNormal[] = "./data/menu/musicon_normal.bmp";
    char szMusiconClicked[] = "./data/menu/musicon_clicked.bmp";
    char szMusicoffNormal[] = "./data/menu/musicoff_normal.bmp";
    char szMusicoffClicked[] = "./data/menu/musicoff_clicked.bmp";
    char *szNoraml,*szClicked;
    int w,h;
    if(theGame->IsMusciOn())
    {
        szNoraml = szMusicoffNormal;
        szClicked = szMusicoffClicked;
    }
    else
    {
        szNoraml = szMusiconNormal;
        szClicked = szMusiconClicked;
    }

    free(item->imgNormal);
    free(item->imgHover);
    free(item->imgClicked);
    item->imgNormal = load_bmpdata(szNoraml,&w,&h);
    item->imgHover  = load_bmpdata(szNoraml,&w,&h);
    item->imgClicked = load_bmpdata(szClicked,&w,&h);

    theGame->MusicSetting();
}

void MenuSoundHandler(void* pParam)
{
    MenuItem *item = (MenuItem*) pParam;
    Game* theGame = (Game*)item->user_data;

    char szSoundonNormal[] = "./data/menu/soundon_normal.bmp";
    char szSoundonClicked[] = "./data/menu/soundon_clicked.bmp";
    char szSoundoffNormal[] = "./data/menu/soundoff_normal.bmp";
    char szSoundoffClicked[] = "./data/menu/soundoff_clicked.bmp";
    char *szNoraml,*szClicked;
    int w,h;
    if(theGame->IsSoundOn())
    {
        szNoraml = szSoundoffNormal;
        szClicked = szSoundoffClicked;
    }
    else
    {
        szNoraml = szSoundonNormal;
        szClicked = szSoundonClicked;
    }

    free(item->imgNormal);
    free(item->imgHover);
    free(item->imgClicked);
    item->imgNormal = load_bmpdata(szNoraml,&w,&h);
    item->imgHover  = load_bmpdata(szNoraml,&w,&h);
    item->imgClicked = load_bmpdata(szClicked,&w,&h);

    theGame->SoundSetting();
}

void MenuBackHandler(void* pParam)
{
    MenuManager *mgr = (MenuManager*)pParam;
    mgr->ShowSubMenu(2,false);
}

bool MenuManager::intialize(Game* game,int width,int height)
{
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

    screenWidth = width;
    screenHeight = height;
    theGame = game;

    addNewItem(szMainNormal,szMainNormal,szMainClicked,10,2,MenuMainHandler,this,0,true,true);
    addNewItem(szSettingNormal,szSettingNormal,szSettingClicked,120,2,MenuSettingHandler,this,0,true,true);
    addNewItem(szNewgameNormal,szNewgameNormal,szNewgameClicked,0,1,MenuNewgameHandler,this,1);
    addNewItem(szLevselectNormal,szLevselectNormal,szLevselectClicked,0,2,MenuLevSelectHandler,this,1);
    addNewItem(szContinueNormal,szContinueNormal,szContinueClicked,0,3,MenuContinueHandler,this,1);
    addNewItem(szQuitNormal,szQuitNormal,szQuitClicked,0,4,MenuQuitHandler,this,1);
    addNewItem(szMusiconNormal,szMusiconNormal,szMusiconClicked,0,1,MenuMusicHandler,(void*)-1,2);
    addNewItem(szSoundonNormal,szSoundonNormal,szSoundonClicked,0,2,MenuSoundHandler,(void*)-1,2);
    addNewItem(szBackNormal,szBackNormal,szBackClicked,0,3,MenuBackHandler,this,2);

    return true;
}

void MenuManager::cleanup()
{
    size_t count = vecMenuItem.size();
    for(size_t idx=0;idx<count;idx++)
    {
        MenuItem *item = vecMenuItem[idx];
        free(item->imgNormal);
        free(item->imgHover);
        free(item->imgClicked);

        delete item;
    }

    vecMenuItem.clear();
}

void MenuManager::newScreenSize(int width,int height)
{
    int oldHeight = screenHeight;
    screenWidth = width;
    screenHeight = height;
    size_t count = vecMenuItem.size();
    for(size_t idx=0;idx<count;idx++)
    {
        MenuItem *item = vecMenuItem[idx];
        if(item->posFixed==true)
            item->yPos += (height-oldHeight);
        else
        {
            int y = screenHeight / 2 + (item->index - 2) * 30;
            item->xPos = (screenWidth - item->width) / 2;
            item->yPos = screenHeight - item->height - y;
            item->x    = item->xPos;
            item->y    = y;
        }
    }
}

void MenuManager::addNewItem(char* szNormal,char* szHover,char* szSelected,
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
        item->user_data = theGame;
    }

    if(fixed==false)
    {
        int y = screenHeight / 2 + (posY - 2) * 30;
        item->xPos = (screenWidth - width) / 2;
        item->x    = item->xPos;
        item->yPos = screenHeight - height - y;
        item->y    = y;

        item->index = posY;
    }

    vecMenuItem.push_back(item);
}

void MenuManager::processMouseMove(float x,float y)
{
    mouseX = x;
    mouseY = y;

    size_t count = vecMenuItem.size();
    for(size_t idx=0;idx<count;idx++)
    {
        if(vecMenuItem[idx]->active)
            hover_menuitem(vecMenuItem[idx]);
    }
}

void MenuManager::processMouseClicked(int button,int action)
{
    if(button == GLFW_MOUSE_BUTTON_LEFT)
    {
        switch(action)
        {
        case GLFW_PRESS:
        case GLFW_RELEASE:
            {
                size_t count = vecMenuItem.size();
                for(size_t idx=0;idx<count;idx++)
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

void MenuManager::hover_menuitem(MenuItem* item)
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

void MenuManager::click_menuitem(MenuItem* item)
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

void MenuManager::drawMenuItems()
{
    Obj::currentShader = 0;
    glUseProgram(0);

    //!< put opengl state to stack
    glPushAttrib(GL_LIGHTING_BIT|GL_DEPTH_BUFFER_BIT|GL_TEXTURE_BIT|GL_CURRENT_BIT);
        //!< close opengl texture light and depth test
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
            glLoadIdentity();
            gluOrtho2D( 0.0, screenWidth, 0.0, screenHeight); 

            size_t count = vecMenuItem.size();
            for(size_t idx=0;idx<count;idx++)
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

void MenuManager::ShowSubMenu(int level,bool bShow)
{
    if(bShow==true)
        theGame->PauseGame();
    else
        theGame->ContinueGame();

    size_t count = vecMenuItem.size();
    for(size_t idx=0;idx<count;idx++)
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
