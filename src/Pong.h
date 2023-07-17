#pragma once
#include "Game.h"

class Pong : public Game{
    public:
        Pong(const char* name, int width, int height); // Constructor
        ~Pong();

        void setup();
        void update();
        void render();
};