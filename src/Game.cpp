#include "Game.h"
#include <print.h>

Game::Game(const char* name, int width, int height)
    : screen_width(width), screen_height(height)
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
    frameDuration = (1.0f / maxFPS) * 1000.0f;
}

Game::~Game()
{
    print("Game destructor called");
}

void Game::setup()
{
    print("Game setup called");
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            setRunning(false);
        };
    }
    print("Game handleEvents called");
}

void Game::update()
{
    print("Game update called");
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}

bool Game::running()
{
    return isRunning;
}

void Game::setRunning(bool value)
{
    isRunning = value;
}

void Game::frameStart()
{
    // Get the current time at the beginning of the frame
    frameStartTimestamp = SDL_GetTicks();

    if (frameEndTimestamp)
    {
        // Calculate the time elapsed since the last frame
        deltaTime = (frameStartTimestamp - frameEndTimestamp) / 1000.0f;
    }
    else
    {
        deltaTime = 0.0f;
    }
}

void Game::frameEnd()
{
    // Get the current time at the end of the frame
    frameEndTimestamp = SDL_GetTicks();

    // Calculate the actual duration of this frame
    float actualFrameDuration = frameEndTimestamp - frameStartTimestamp;

    // Delay to achieve the target frame rate
    if (actualFrameDuration < frameDuration)
    {
        SDL_Delay(static_cast<Uint32>(frameDuration - actualFrameDuration));
    }

    // FPS calculation
    frameCountPerSecond++;
    Uint32 currentTime = SDL_GetTicks();
    Uint32 timeElapsed = currentTime - lastFPSUpdate;

    if (timeElapsed >= 1000)
    {
        FPS = static_cast<double>(frameCountPerSecond) / (timeElapsed / 1000.0);
        lastFPSUpdate = currentTime;
        frameCountPerSecond = 0;
    }
}
