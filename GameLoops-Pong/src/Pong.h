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
    void frameStart();
    void frameEnd();

private:
    SDL_Rect ball;
    SDL_Rect paddle1;
    SDL_Rect paddle2;
    float ball_speed_x;
    float ball_speed_y;
    float ball_speed_multiplier;

    bool isGameOver;
    SDL_Rect gameOverRect;

protected:
    // FPS handle
    double FPS;
    int frameCountPerSecond;
    Uint32 frameStartTimestamp;
    Uint32 frameEndTimestamp;
    Uint32 lastFPSUpdate;
    float deltaTime;

};
