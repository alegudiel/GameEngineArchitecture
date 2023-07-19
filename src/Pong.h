#pragma once
#include "Game.h"

class Pong : public Game {
public:
    Pong(const char* name, int width, int height); // Constructor
    ~Pong();

    void setup();
    void frameStart();
    void frameEnd();
    void handleEvents();
    void update();
    void render();
    bool running();

private:
    bool isRunning(); 
    SDL_Rect ball;
    SDL_Rect paddle1; // First player paddle
    SDL_Rect paddle2; // Second player paddle
    int ball_speed_x;
    int ball_speed_y;
    int width;
    int height;

    SDL_Window* window;
    SDL_Renderer* renderer;

    int screen_width;
    int screen_height;
};
