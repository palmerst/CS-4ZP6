#include "Game.h"

#include <stdio.h>

//
/*** For systems using nvidia optimus GPUs ***/
extern "C" {
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}

int main(int argc, char** argv)
{
    /*** Start new game ***/
    Game* gameInstance = new Game();

    /*** Run the game ***/
    gameInstance->run();

    return 0;
}

