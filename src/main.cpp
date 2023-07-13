// Hello world :)

#include <iostream>
#include "print.h"
#include "Game.h"
#include <string>

int main(){
    Game pong = Game("pong", 800, 600);

    pong.setup();

    while(pong.running()){
        pong.frameStart();

        pong.handleEvents();
        pong.update();
        pong.render();

        pong.frameEnd();
    }

}