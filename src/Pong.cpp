
#include "Pong.h"
#include "Game.h"

Pong::Pong(const char* name, int width, int height)
    : Game(name, width, height)
{
}

Pong::~Pong() {

}

void Pong::setup() {

    // Set initial positions and sizes of the ball and paddles

    ball.x = 20;
    ball.y = 20;
    ball.w = 20;
    ball.h = 20;

    paddle1.x = (screen_width / 2) - 50;
    paddle1.y = screen_height - 20;
    paddle1.w = 100;
    paddle1.h = 20;

    paddle2.x = (screen_width / 2) - 50;
    paddle2.y = 20;
    paddle2.w = 100;
    paddle2.h = 20;

    // Set initial ball speed
    ball_speed_x = 5;
    ball_speed_y = 5;
}

void Pong::update() {
    // Update ball movement

    if (ball.x < 0 || ball.x > screen_width - ball.w) {
        ball_speed_x *= -1;
    }

    if (ball.y < 0 || ball.y > screen_height - ball.h) {
        ball_speed_y *= -1;
    }

    ball.x += ball_speed_x;
    ball.y += ball_speed_y;
}

void Pong::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
    SDL_RenderClear(renderer);

    // Draw the game

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderFillRect(renderer, &ball);
    SDL_RenderFillRect(renderer, &paddle1);
    SDL_RenderFillRect(renderer, &paddle2);

    SDL_RenderPresent(renderer);
}

void Pong::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            setRunning(false);
        }

        // Handle paddle movements for both players

        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                paddle1.x -= 10;
                break;
            case SDLK_RIGHT:
                paddle1.x += 10;
                break;
            case SDLK_a:
                paddle2.x -= 10;
                break;
            case SDLK_d:
                paddle2.x += 10;
                break;
            }
        }

        // Bounce the ball on the paddles

        if (ball.y + ball.h >= paddle1.y && ball.x + ball.w >= paddle1.x && ball.x <= paddle1.x + paddle1.w) {
            ball_speed_y *= -1;
        }

        if (ball.y <= paddle2.y + paddle2.h && ball.x + ball.w >= paddle2.x && ball.x <= paddle2.x + paddle2.w) {
            ball_speed_y *= -1;
        }

        // Check if the ball hits the screen boundaries

        if (ball.y + ball.h >= screen_height || ball.y <= 0) {
            setRunning(false);
        }
    }
}

bool Pong::running() {
    return Game::isRunning; // Access the isRunning member variable from the base class Game
}
