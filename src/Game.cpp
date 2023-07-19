#include "Game.h"
#include <print.h>

Game::Game(const char* name, int width, int height)
    :screen_width(width), screen_height(height)
{
    isRunning = true;
    print("Game constructor called");
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(name, 0, 0, width, height, 0);
    renderer = SDL_CreateRenderer(window, 0, 0);

    // para los FPS
    lastFPSUpdate = 0;
    frameStartTimestamp = 0;
    frameEndTimestamp = 0;
    frameCountPerSecond = 0;
    FPS = 0.0;

    int maxFPS = 60;
    frameDuration = (1.0f / maxFPS) * 1000.0f ;
};

Game::~Game()
{
    print("Game destructor called");
};

void Game::setup()
{
    print("Game setup called");
};

void Game::frameStart()
{
    print("Game frameStart called");

    if(frameEndTimestamp){
        deltaTime = (frameStartTimestamp - frameEndTimestamp) / 1000.0f;
    } else{
        deltaTime = 0.0f;
    }
};

void Game::frameEnd()
{
    print("Game frameEnd called");
    frameEndTimestamp = SDL_GetTicks();

    // Delay
    float actualFrameDuration = frameEndTimestamp - frameStartTimestamp;
    if(actualFrameDuration < frameDuration){
        SDL_Delay(frameDuration - actualFrameDuration);
    }

    // FPS calcs
    frameCountPerSecond++;
    Uint32 currentTime = SDL_GetTicks();
    Uint32 timeElapsed = currentTime - lastFPSUpdate;

if(timeElapsed > 1000)
    {
        // va entrar cada segundo
        FPS = (frameCountPerSecond / timeElapsed) / 1000;
        lastFPSUpdate = currentTime;
        frameCountPerSecond = 0;
    }
    print("FPS ---->", FPS);
};

void Game::handleEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event) !=0 ){
        if(event.type == SDL_QUIT)
        {
            setRunning(false);
        };
    }
    print("Game handleEvents called");
};

void Game::update()
{
    print("Game update called");
};

void Game::render()
{
    print("Game render called");
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
};

bool Game::running() {
    return isRunning;
}

void Game::setRunning(bool value) {
    isRunning = value;
}
