#include "Game.h"
#include "print.h"

Game::Game(const std::string& name, int width, int height)
{
    print("Game constructor called");
};

Game::~Game()
{
    print("Game destructor called");
};

void Game::setup()
{
    print("Game setup called");
};

void Game::frameStart()
{
    print("Game frameStart called");
};

void Game::frameEnd()
{
    print("Game frameEnd called");
};

void Game::handleEvents()
{
    print("Game handleEvents called");
};

void Game::update()
{
    print("Game update called");
};

void Game::render()
{
    print("Game render called");
};

bool Game::running()
{
    return isRunning;
};

