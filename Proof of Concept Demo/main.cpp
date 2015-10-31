#include "Game.h"

/*** For systems using nvidia optimus GPUs ***/
extern "C" {
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}

int main(int argc, char** argv)
{

    Game* gameInstance = new Game();

    gameInstance->run();

    return 0;
}

