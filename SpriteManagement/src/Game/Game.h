#include <SDL2/SDL.h>
#include <memory>
#include "Scene/Scene.h"


class Game {
    public:
        Game(const char* title, int width, int height);
        ~Game();

        void setup();
        void frameStart();
        void frameEnd();
        void handleEvents();
        void update();
        void render();
        void clean();
        bool running();

        void run();

        void setScene(std::unique_ptr<Scene> newScene);
        Scene* getCurrentScene() const;

    protected:
        bool isRunning;
        SDL_Window *window;
        SDL_Renderer *renderer;

        int screen_width;
        int screen_height;

        // for frame management
        Uint32 frameStartTimestamp;
        Uint32 frameEndTimestamp;
        float frameDuration;
        float dT; // time in miliseconds since last frame
        // for frame count
        int frameCount;
        Uint32 lastFPSUpdateTime;
        float FPS;

        // scene logic
        std::unique_ptr<Scene> currentScene;
};