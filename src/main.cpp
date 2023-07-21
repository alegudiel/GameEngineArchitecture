// Game loops - pong game

#include <string>
#include <SDL2/SDL.h>
#include "Pong.h"

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // Handle SDL initialization error
        return -1;
    }

    // Create the Pong game instance
    Pong pongGame("Pong", 800, 600);

    // Setup the game
    pongGame.setup();

    // Start the game loop
    while (pongGame.running()) {
        pongGame.handleEvents();
        pongGame.update();
        pongGame.render();
    }

    // Clean up SDL
    SDL_Quit();
    return 0;
}
