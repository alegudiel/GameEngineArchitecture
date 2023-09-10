#pragma once
#include "Game/Game.h"


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Pong : public Game {
    public:
        Pong();
        ~Pong();

    private:
        std::unique_ptr<Scene> createGameplayScene();
};