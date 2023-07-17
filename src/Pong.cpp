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
}

void Pong::update(){
    print("Pong update called");
}

void Pong::render(){
    print("Pong render called");
}