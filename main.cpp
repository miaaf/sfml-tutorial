#include <iostream>
#include "Game.h"


/*
    author: miaf
    license: MIT License
*/

using namespace std;

int main(){
    //random seed
    srand(static_cast<unsigned>(time(NULL)));

    //init game engine
    Game game;

    //game loop
    while (game.isRunning())
    {
        //Update
        game.update();

        //Render
        game.render();
    }
    //end of application
    return 0;
}
