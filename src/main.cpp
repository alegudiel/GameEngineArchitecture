// Game loops - pong game

#include <string>
#include "Pong.h"

Game *game = NULL;

int main( int argc, char* args[] )
{
    game = new Pong("Pongsito", 800, 600);

    game->setup();

    while (game->running())
    {
      game->frameStart();
      game->handleEvents();
      game->update();
      game->render();
      game->frameEnd();
    }

    return 0;

}