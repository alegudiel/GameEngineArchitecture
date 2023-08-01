#pragma once
#include <glm/glm.hpp>
#include <string>

struct NameComponent {
    std::string name;
};

struct TransformComponent {
    glm::vec2 position;
    glm::vec2 scale;
    float rotation;
};

struct MovementComponent {
    glm::vec2 velocity;
};

