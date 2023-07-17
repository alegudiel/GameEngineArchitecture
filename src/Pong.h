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
        SDL_Rect paddle1; // First player paddle
        SDL_Rect paddle2; // Second player paddle
        int ball_speed_x;
        int ball_speed_y;
        int width;
        int height;
        bool isRunning;

        SDL_Window* window;
        SDL_Renderer* renderer;

        int screen_width;
        int screen_height;
};
