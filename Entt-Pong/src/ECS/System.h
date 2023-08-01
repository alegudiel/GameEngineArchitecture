#pragma once

#include <SDL2/SDL.h>
#include "Scene/Scene.h"

class System {
    protected:
        Scene* scene;

    public:
        void setScene(Scene* s) { scene = s; };
};

class SetupSystem : public System {
    public:
        virtual void run() = 0;
};

class EventSystem : public System {
    public:
        virtual void run(SDL_Event event) = 0;
};

class UpdateSystem : public System {
    public:
        virtual void run(double dT) = 0;
};

class RenderSystem : public System {
    public:
        virtual void run(SDL_Renderer* renderer) = 0;
};