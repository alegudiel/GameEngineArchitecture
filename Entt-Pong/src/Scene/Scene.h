#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <entt/entt.hpp>

class Scene{
    public:
        Scene(const sttd::string& name);
        ~Scene();

        entt:registry r;

    private:
        sttd::string name;
}