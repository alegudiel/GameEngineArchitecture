#include "../ECS/Entity.h"
#include "Pong.h"
#include "Systems.h"
#include "Components.h"

Pong::Pong() : Game("Pong", SCREEN_WIDTH, SCREEN_HEIGHT) {
    std::unique_ptr<Scene> gameplayScene = createGameplayScene();
    setScene(std::move(gameplayScene));
}

Pong::~Pong() {
    // Destructor implementation
}

std::unique_ptr<Scene> Pong::createGameplayScene()
{
    // Create a unique_ptr to hold the created scene
    std::unique_ptr<Scene> gameplayScene = std::make_unique<Scene>("Gameplay");

    Entity ball = gameplayScene->createEntity("ball", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    ball.addComponent<SpeedComponent>(200, 200);
    ball.addComponent<SizeComponent>(30, 30);
    ball.addComponent<ColliderComponent>(false);

    // Create the first player's paddle
    Entity paddle1 = gameplayScene->createEntity("paddle1", 20, (SCREEN_HEIGHT / 2) - 50);
    paddle1.addComponent<SpeedComponent>(0, 0);
    paddle1.addComponent<SizeComponent>(20, 100);
    paddle1.addComponent<PlayerComponent>(100, 200);

    // Create the second player's paddle
    Entity paddle2 = gameplayScene->createEntity("paddle2", SCREEN_WIDTH - 40, (SCREEN_HEIGHT / 2) - 50);
    paddle2.addComponent<SpeedComponent>(0, 0);
    paddle2.addComponent<SizeComponent>(20, 100);
    paddle2.addComponent<PlayerComponent>(100, 100);

    gameplayScene->addEventSystem<PlayerInputEventSystem>();
    gameplayScene->addUpdateSystem<MovementUpdateSystem>(SCREEN_WIDTH, SCREEN_HEIGHT);
    gameplayScene->addUpdateSystem<CollisionDetectionUpdateSystem>();
    gameplayScene->addUpdateSystem<BounceUpdateSystem>();
    gameplayScene->addRenderSystem<RectRenderSystem>();

    return gameplayScene;
}
