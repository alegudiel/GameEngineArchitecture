#include <print.h>

#include "ECS/Entity.h"
#include "Game/Graphics/PixelShader.h"

#include "Pong/Pong.h"
#include "Pong/Systems.h"


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

    scene->addSetupSystem(new SpriteSetupSystem(renderer));
    scene->addRenderSystem(new SpriteRenderSystem());
    scene->addUpdateSystem(new SpriteUpdateSystem());

    gameplayScene->addEventSystem<PlayerInputEventSystem>();
    gameplayScene->addUpdateSystem<MovementUpdateSystem>(SCREEN_WIDTH, SCREEN_HEIGHT);
    gameplayScene->addUpdateSystem<CollisionDetectionUpdateSystem>();
    gameplayScene->addUpdateSystem<BounceUpdateSystem>();
    gameplayScene->addRenderSystem<RectRenderSystem>();

    return gameplayScene;
}
