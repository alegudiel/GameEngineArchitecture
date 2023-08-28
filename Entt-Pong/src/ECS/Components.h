#pragma once

#include <glm/glm.hpp>
#include <string>

struct NameComponent {
    std::string tag;
};

struct TransformComponent {
    glm::ivec2 position;
};

struct SpeedComponent {
    int x;
    int y;
};