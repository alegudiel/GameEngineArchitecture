#pragma once

#include <iostream>
#include "ECS/System.h"

class HelloSystem : public SetupSystem {
    public:
        HelloSystem();
        HelloSystem(const HelloSystem& other);
        ~HelloSystem();

        void run() override;
};

class RectRenderSystem : public RenderSystem {
    public:
        void run(SDL_Renderer* renderer) override;
};

class MovementUpdateSystem : public UpdateSystem {
    public:
        MovementUpdateSystem(int screen_width, int screen_height);

        void run(double dT) override;

    private:
        int screen_width;
        int screen_height;
};

class PlayerInputEventSystem : public EventSystem {
    public:
        void run(SDL_Event event) override;
};

class CollisionDetectionUpdateSystem : public UpdateSystem {
    public:
        void run(double dT);
};

class BounceUpdateSystem : public UpdateSystem {
    public:
        void run(double dT);
};