#include "Pong.h"
#include "Game.h"

Pong::Pong(const char* name, int width, int height)
    : Game(name, width, height)
{
    // Initialize the "Game Over" message variables
    isGameOver = false;
    gameOverTexture = nullptr;
    gameOverRect = { width / 2 - 100, height / 2 - 50, 200, 100 };
}

Pong::~Pong()
{
    // Clean up the "Game Over" message texture
    if (gameOverTexture != nullptr)
    {
        SDL_DestroyTexture(gameOverTexture);
        gameOverTexture = nullptr;
    }
}

void Pong::setup()
{
    // Set initial sizes of the ball 
    ball.x = 20;
    ball.y = 20;
    ball.w = 20;
    ball.h = 20;

    // Set initial position of the paddles
    paddle1.x = (screen_width / 2) - 50;
    paddle1.y = screen_height - 20;
    paddle1.w = 100;
    paddle1.h = 20;

    paddle2.x = (screen_width / 2) - 50;
    paddle2.y = 20;
    paddle2.w = 100;
    paddle2.h = 20;

    // Set initial ball speed
    ball_speed_x = 1;
    ball_speed_y = 1;
    ball_speed_multiplier = 0.5;
}

void Pong::update()
{
    // Update ball movement
    if (ball.x < 0 || ball.x > screen_width - ball.w)
    {
        ball.x += ball_speed_x * ball_speed_multiplier;
    }

    if (ball.y < 0 || ball.y > screen_height - ball.h)
    {
        ball.y += ball_speed_y * ball_speed_multiplier;

        // Set "Game Over" flag to true when the ball hits the top or bottom boundary
        isGameOver = true;
    }

    ball.x += ball_speed_x;
    ball.y += ball_speed_y;
}

void Pong::render()
{
    SDL_SetRenderDrawColor(renderer, 255, 153, 204, 1);
    SDL_RenderClear(renderer);

    // Draw the game
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderFillRect(renderer, &ball);
    SDL_RenderFillRect(renderer, &paddle1);
    SDL_RenderFillRect(renderer, &paddle2);

    // Render "Game Over" message if the game is over
    if (isGameOver)
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &gameOverRect);
    }

    SDL_RenderPresent(renderer);
}

void Pong::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            setRunning(false);
        }

        // Handle paddle movements for both players
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                paddle1.x -= 30;
                break;
            case SDLK_RIGHT:
                paddle1.x += 30;
                break;
            case SDLK_a:
                paddle2.x -= 30;
                break;
            case SDLK_d:
                paddle2.x += 30;
                break;
            }
        }
    }

    // Bounce the ball on the paddles
    if (ball.y + ball.h >= paddle1.y && ball.x + ball.w >= paddle1.x && ball.x <= paddle1.x + paddle1.w)
    {
        // Reverse ball's y-direction when it collides with paddle1
        ball_speed_y *= -1;
    }

    if (ball.y <= paddle2.y + paddle2.h && ball.x + ball.w >= paddle2.x && ball.x <= paddle2.x + paddle2.w)
    {
        // Reverse ball's y-direction when it collides with paddle2
        ball_speed_y *= -1;
    }

    // Check if the ball hits the screen boundaries
    if (ball.y + ball.h >= screen_height || ball.y <= 0)
    {
        setRunning(false);
    }
}
