#include <print.h>

#include "Pong.h"
#include "Systems.h"

#include "ECS/Entity.h"

#include "Game/Graphics/PixelShader.h"

Pong::Pong(const char* name, int width, int height)
  : Game(name, width, height)
{
  Scene* gameplayScene = createGameplayScene();
  setScene(gameplayScene);
}

Pong::~Pong() {
  
}

Scene* Pong::createGameplayScene() {
  Scene* scene = new Scene("GAMEPLAY SCENE");
  
  scene->addSetupSystem(new WorldSetupSystem());
  scene->addSetupSystem(new CameraSetupSystem());
  scene->addSetupSystem(new PlayerSetupSystem());

  scene->addSetupSystem(new TilemapSetupSystem(renderer));
  scene->addSetupSystem(new AutoTilingSetupSystem());
  scene->addRenderSystem(new TilemapRenderSystem());

  scene->addSetupSystem(new SpriteSetupSystem(renderer));
  scene->addRenderSystem(new SpriteRenderSystem());
  scene->addUpdateSystem(new SpriteUpdateSystem());


  scene->addEventSystem(new PlayerInputSystem());
  scene->addUpdateSystem(new TileCollisionUpdateSystem());
  scene->addUpdateSystem(new MovementUpdateSystem());
  scene->addUpdateSystem(new PlayerSpriteUpdateSystem());
  scene->addUpdateSystem(new CameraFollowUpdateSystem());

  scene->addRenderSystem(new ColliderRenderSystem());
  scene->addRenderSystem(new TileColliderRenderSystem());

  return scene;
}
