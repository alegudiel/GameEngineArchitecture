#include "ECS/Components.h"

struct SizeComponent {
    int w;
    int h;
};

struct PlayerComponent {
    int moveSpeed;
};

struct ColliderComponent {
    bool triggered;
    int transferSpeed;
};