#include <print.h>
#include "Pong.h"

Pong::Pong(const char* name, int width, int height)
    : Game(name, width, height)
{
}

Pong::~Pong(){

}

void Pong::setup(){
    print("Pong setup called");

    // donde esta
    ball.x = 20;
    ball.y = 20;
    // cuanto mide
    ball.w = 20;
    ball.h = 20;

    // velocidad de la pelota
    ball_speed_x = 5;
    ball_speed_y = 5;

    paddle.x = (screen_width/2) - 50;
    paddle.y = screen_height - 20;
    paddle.w = 100;
    paddle.h = 20;

}

void Pong::update(){
    print("MOVEMENT");
    // verify that the ball doesn't falls out of screen
    if(ball.x < 0 || ball.x > screen_width - ball.w){
        ball_speed_x *= -1;
    }
    if(ball.y < 0 || ball.y > screen_height - ball.h){
        ball_speed_y *= -1;
    }

    // move ball per the frame 
    ball.x += ball_speed_x;
    ball.y += ball_speed_y;

}

void Pong::render(){
    print("Pong render called");
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
    SDL_RenderClear(renderer);

    //------- draw game

    //set the colors for the paddle and ball
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // fill the paddle and ball
    SDL_RenderFillRect(renderer, &ball);
    SDL_RenderFillRect(renderer, &paddle);

    // 
    SDL_RenderPresent(renderer);

}

void Pong::handleEvents(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT){
            isRunning = false; 
        }
        // moving the paddle 
        if(event.type == SDL_KEYDOWN){
            switch(event.key.keysym.sym){
                case SDLK_LEFT:
                    paddle.x -= 10;
                    break;
                case SDLK_RIGHT:
                    paddle.x += 10;
                    break;
            }
        }
        // bouncing the ball on the paddle
        if(ball.y + ball.h >= paddle.y && ball.x + ball.w >= paddle.x && ball.x <= paddle.x + paddle.w){
            ball_speed_y *= -1;
        }
        // when ball doesnt hits the paddle but it hits the screen, game over
        if(ball.y + ball.h >= screen_height){
            isRunning = false;
        }
    }
}