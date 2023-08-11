#pragma once
#include <string>
#include <entt/entt.hpp>

class Scene {
    public:
        Scene(const std::string& name);
        ~Scene();

        entt::registry r;

    private:
        std::string name;
};