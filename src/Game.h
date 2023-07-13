#pragma once
#include <string>

class Game
{
    public:
        Game(const std::string& name, int width, int height); // Constructor
        ~Game(); // Destructor

        void setup();
        void frameStart();
        void frameEnd();
        void handleEvents();
        void update();
        void render();
        bool running();

    private:
        int width;
        int height;
        bool isRunning;

};