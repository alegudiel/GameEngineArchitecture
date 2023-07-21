#pragma once
#include "Game.h"

class Pong : public Game {
public:
    Pong(const char* name, int width, int height); // Constructor
    ~Pong();

    void setup() override;
    void handleEvents() override;
    void update() override;
    void render() override;

private:
    SDL_Rect ball;
    SDL_Rect paddle1;
    SDL_Rect paddle2;
    float ball_speed_x;
    float ball_speed_y;
    float ball_speed_multiplier;

    bool isGameOver;
    SDL_Texture* gameOverTexture;
    SDL_Rect gameOverRect;

};
