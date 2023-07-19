#pragma once
#include <SDL2/SDL.h>
#include <string>

class Game
{
    public:
        Game(const char* name, int width, int height); // Constructor
        virtual ~Game(); // Destructor

        void setup();
        void frameStart();
        void frameEnd();
        void handleEvents();
        void update();
        void render();
        bool running();
        void setRunning(bool value);

    
        bool isRunning;

    private:
        int width;
        int height;

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