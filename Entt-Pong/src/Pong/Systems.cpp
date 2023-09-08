#include "print.h"
#include "Systems.h"
#include "Components.h"

void RectRenderSystem::run(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);

    const auto view = scene->r.view<TransformComponent, SizeComponent>();
    for (const entt::entity e : view) {
        const TransformComponent& transform = view.get<TransformComponent>(e);
        const SizeComponent& size = view.get<SizeComponent>(e);
        const int x = transform.position.x;
        const int y = transform.position.y;
        const int w = size.w;
        const int h = size.h;

        SDL_Rect rect = { x, y, w, h };
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
}

MovementUpdateSystem::MovementUpdateSystem(int screen_width, int screen_height)
    : screen_width(screen_width), screen_height(screen_height) { }

// MovementUpdateSystem
void MovementUpdateSystem::run(double dT) {
    const auto view = scene->r.view<TransformComponent, SpeedComponent, NameComponent>();
    for (const entt::entity e : view){
        TransformComponent& t = view.get<TransformComponent>(e);
        SpeedComponent& speed = view.get<SpeedComponent>(e);
        NameComponent& name = view.get<NameComponent>(e);

        //----->Ball movement        
        if (name.tag == "ball") {
            // Check for collision with top boundary
            if (t.position.y <= 0) {
                speed.y *= -1; // Reverse the y direction
            }
            // Check for collision with bottom boundary
            if (t.position.y >= screen_height - 20) {
                speed.y *= -1; // Reverse the y direction
            }

            // Check for collision with right and left boundary
            if (t.position.x > screen_width - 20 ) {
                print("Player 1 wins!");
                exit(1); // Exit the program
            }
            if (t.position.x < 0) {
                print("Player 2 wins!");
                exit(1); // Exit the program
            }
        }
        
        // Update position based on speed and time step
        t.position.x += speed.x * dT;
        t.position.y += speed.y * dT;
        //----->End ball movement
    }
}

// PlayerInputEventSystem
void PlayerInputEventSystem::run(SDL_Event event) {
    scene->r.view<PlayerComponent, SpeedComponent>().each(
    [&](const auto& entity, PlayerComponent& player, SpeedComponent& speed) {
        // exit(1);
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym) {
            case SDLK_s: // Player 1: Move Down
                if (player.playerType == 200) {
                    speed.y = player.moveSpeed;
                }
                break;
            case SDLK_w: // Player 1: Move Up
                if (player.playerType == 200) {
                    speed.y = -player.moveSpeed;
                }
                break;
            case SDLK_DOWN: // Player 2: Move Down
                if (player.playerType == 100) {
                    speed.y = player.moveSpeed;
                }
                break;
            case SDLK_UP: // Player 2: Move Up
                if (player.playerType == 100) {
                    speed.y = -player.moveSpeed;
                }
                break;
            }
        }
        if (event.type == SDL_KEYUP)
        {
            switch (event.key.keysym.sym) {
            case SDLK_w: // Player 1: Stop moving
            case SDLK_s:
                if (player.playerType == 200) {
                    speed.y = 0;
                }
                break;
            case SDLK_UP: // Player 2: Stop moving
            case SDLK_DOWN:
                if (player.playerType == 100) {
                    speed.y = 0;
                }
                break;
            }
        }
    });
}


// CollisionDetectionUpdateSystem
void CollisionDetectionUpdateSystem::run(double dT) {
    const auto view = scene->r.view<TransformComponent, SizeComponent, ColliderComponent>();
    const auto view2 = scene->r.view<TransformComponent, SizeComponent>();

    view.each([&](auto e1, TransformComponent& t1, SizeComponent& s1, ColliderComponent& c1) {
        // Create a bounding box for the first entity
        SDL_Rect box1 = { t1.position.x, t1.position.y, s1.w, s1.h };

        // Check against all other entities
        view2.each([&](auto e2, TransformComponent& t2, SizeComponent& s2) {
            if (e1 == e2) return;  // Skip self

            // Create a bounding box for the second entity
            SDL_Rect box2 = { t2.position.x, t2.position.y, s2.w, s2.h };

            // Check for intersection
            if (SDL_HasIntersection(&box1, &box2)) {
                c1.triggered = true;
            }
        });
    });
}

void BounceUpdateSystem::run(double dT) {
    const auto view = scene->r.view<ColliderComponent, SpeedComponent>();

    view.each([&](auto e, ColliderComponent& c, SpeedComponent& s) {
        if (c.triggered) {
            c.triggered = false;
            s.x = -1;
        }
    });
}