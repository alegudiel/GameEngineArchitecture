#pragma once

#include <SDL_events.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <print.h>
#include <FastNoise.h>
#include <random>
#include <ctime>

#include "TextureManager.h"
#include "Pong/Components.h"

#include "ECS/Components.h"
#include "ECS/Entity.h"
#include "ECS/SystemTypes/SetupSystem.h"
#include "ECS/SystemTypes/SystemTypes.h"
#include "ECS/SystemTypes/UpdateSystem.h"


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

class SpriteSetupSystem : public SetupSystem {
    public:
        SpriteSetupSystem(SDL_Renderer* renderer)
        : renderer(renderer) { }

        ~SpriteSetupSystem() {
        auto view = scene->r.view<SpriteComponent>();

        for(auto entity : view) {
            const auto spriteComponent = view.get<SpriteComponent>(entity);
    
            TextureManager::UnloadTexture(spriteComponent.name, spriteComponent.shader.name);
        }
        }

        void run() {
        auto view = scene->r.view<SpriteComponent>();

        for(auto entity : view) {
            const auto spriteComponent = view.get<SpriteComponent>(entity);
    
            TextureManager::LoadTexture(spriteComponent.name, renderer, spriteComponent.shader);
            }
        }

    private:
        SDL_Renderer* renderer;
};

class SpriteRenderSystem : public RenderSystem {
    public:
        void run(SDL_Renderer* renderer) {
        auto view = scene->r.view<TransformComponent, SpriteComponent>();

        for(auto entity : view) 
        {
            const auto spriteComponent = view.get<SpriteComponent>(entity);
            const auto transformComponent = view.get<TransformComponent>(entity);
    
            Texture* texture = TextureManager::GetTexture(spriteComponent.name, spriteComponent.shader.name);
    
            SDL_Rect clip = {
            spriteComponent.xIndex * spriteComponent.size,
            spriteComponent.yIndex * spriteComponent.size,
            spriteComponent.size,
            spriteComponent.size
            };

            texture->render(
            transformComponent.x - c.x,
            transformComponent.y - c.y,
            48 * z,
            48 * z,
            &clip
            );
        }
    }
};

class SpriteUpdateSystem : public UpdateSystem {
    public:
        void run(float dT) {
        auto view = scene->r.view<SpriteComponent>();

        Uint32 now = SDL_GetTicks();

        for(auto entity : view) {
            auto& spriteComponent = view.get<SpriteComponent>(entity);

            if (spriteComponent.animationFrames > 0) 
            {
                float timeSinceLastUpdate = now - spriteComponent.lastUpdate;

                int framesToUpdate = static_cast<int>(
                    timeSinceLastUpdate / 
                    spriteComponent.animationDuration * spriteComponent.animationFrames
                );

                if (framesToUpdate > 0) {
                    spriteComponent.xIndex += framesToUpdate;
                    spriteComponent.xIndex %= spriteComponent.animationFrames;
                    spriteComponent.lastUpdate = now;            
                    }
            }
        }
    }
};