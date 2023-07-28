#pragma once
#include <SDL2/SDL.h>
#include <string>

class Game
{
public:
    Game(const char* name, int width, int height); // Constructor
    virtual ~Game(); // Destructor

    virtual void setup();
    virtual void handleEvents();
    virtual void update();
    virtual void render();
    bool running();
    void setRunning(bool value);

    void frameStart();
    void frameEnd();

protected:
    int width;
    int height;

    SDL_Window* window;
    SDL_Renderer* renderer;

    int screen_width;
    int screen_height;

    // FPS
    double FPS;
    int frameCountPerSecond;
    // Frame management
    Uint32 frameStartTimestamp;
    Uint32 frameEndTimestamp;
    Uint32 lastFPSUpdate;
    float frameDuration;
    // Delta time
    float deltaTime; // time in milliseconds since the last frame

    bool isRunning;
};
