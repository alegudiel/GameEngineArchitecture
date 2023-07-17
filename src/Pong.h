#pragma once
#include "Game.h"

class Pong : public Game{
    public:
        Pong(const char* name, int width, int height); // Constructor
        ~Pong();

        void setup() override;
        void update() override;
        void render() override;
        void handleEvents() override;

    private:
        SDL_Rect ball;
        SDL_Rect paddle;
        int ball_speed_x;
        int ball_speed_y;
};