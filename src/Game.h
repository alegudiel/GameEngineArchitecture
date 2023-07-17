#pragma once
#include <SDL2/SDL.h>
#include <string>

class Game
{
    public:
        Game(const char* name, int width, int height); // Constructor
        ~Game(); // Destructor

        virtual void setup() = 0;
        void frameStart();
        void frameEnd();
        virtual void handleEvents() = 0;
        virtual void update() = 0;
        virtual void render() = 0;
        bool running();

        void run();

    private:
        int width;
        int height;
        bool isRunning;

        SDL_Window* window;
        SDL_Renderer* renderer;

        int screen_width;
        int screen_height;

        //FPS
        double FPS;
        int frameCountPerSecond;
        // frame management
        Uint32 frameStartTimestamp;
        Uint32 frameEndTimestamp;
        Uint32 lastFPSUpdate;
        float frameDuration;
        // Delta time
        float deltaTime; // time in miliseconds a partir del lastFrame
};