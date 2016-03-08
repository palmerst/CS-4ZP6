#include "Game.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    /*** Start new game ***/
    Game* gameInstance = new Game(argc, argv);

    /*** Run the game ***/
    gameInstance->run();

    return 0;
}

