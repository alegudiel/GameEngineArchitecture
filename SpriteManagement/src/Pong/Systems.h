#pragma once
#include <SDL_events.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <print.h>
#include <FastNoise.h>
#include <random>
#include <ctime>

#include "Components.h"

#include "ECS/Components.h"
#include "ECS/Entity.h"
#include "ECS/SystemTypes/SetupSystem.h"
#include "ECS/SystemTypes/SystemTypes.h"

#include "ECS/SystemTypes/UpdateSystem.h"
#include "Game/Graphics/TextureManager.h"


class HelloWorldSystem : public SetupSystem {
  public:
    HelloWorldSystem() {
      print("Hello World Constructor");
    }

    ~HelloWorldSystem() {
      print("Hello World Destructor");
    }

    void run() {
      print("Hello World run!");
    }
};

class MovementUpdateSystem : public UpdateSystem {
  public:
    void run(float dT) {
      const auto view = scene->r.view<TransformComponent, SpeedComponent>();

      for (const auto entity : view) {
        auto& t = view.get<TransformComponent>(entity);
        auto& s = view.get<SpeedComponent>(entity);

        if (s.x == 0 && s.y == 0) {
          continue;
        }

        t.x += s.x * dT;
        t.y += s.y * dT;
      }
  }
};


class PlayerInputSystem : public EventSystem {
  void run(SDL_Event event) {
    auto& playerSpeed = scene->player->get<SpeedComponent>();
    int speed = 200;

    if (event.type == SDL_KEYDOWN) {
      switch(event.key.keysym.sym) {
        case SDLK_RIGHT:
          playerSpeed.x = speed;
          break;
        case SDLK_LEFT:
          playerSpeed.x = -speed;
          break;
        case SDLK_UP:
          playerSpeed.y = -speed;
          break;
        case SDLK_DOWN:
          playerSpeed.y = speed;
          break;
      }
    }
    if (event.type == SDL_KEYUP) {
      switch(event.key.keysym.sym) {
        case SDLK_RIGHT:
          playerSpeed.x = 0;
          break;
        case SDLK_LEFT:
          playerSpeed.x = 0;
          break;
        case SDLK_UP:
          playerSpeed.y = 0;
          break;
        case SDLK_DOWN:
          playerSpeed.y = 0;
          break;
      }
    }
  }
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
      const auto c = scene->mainCamera->get<TransformComponent>();
      const auto z = scene->mainCamera->get<CameraComponent>().zoom;

      for(auto entity : view) {
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

        if (spriteComponent.animationFrames > 0) {
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


class TilemapSetupSystem : public SetupSystem {
  public:
    TilemapSetupSystem(SDL_Renderer* renderer)
      : renderer(renderer) { }

    ~TilemapSetupSystem() {
    }

    void run() {
      const auto playerPosition = scene->player->get<TransformComponent>();
      const auto z = scene->mainCamera->get<CameraComponent>().zoom;
      Texture* waterTexture = TextureManager::LoadTexture("Tilesets/Water.png", renderer);
      Texture* grassTexture = TextureManager::LoadTexture("Tilesets/Grass.png", renderer);

      auto& tilemap = scene->world->get<TilemapComponent>();
      tilemap.map.resize(tilemap.width * tilemap.height);

      std::srand(std::time(nullptr));
      float offsetX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
      float offsetY = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
      float zoom = 20.0f;
      FastNoiseLite noise;
      noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);

      Terrain grass{grassTexture};
      Terrain water{waterTexture};

      int centerX = playerPosition.x / z / tilemap.tileSize;
      int centerY = playerPosition.y / z / tilemap.tileSize;

      for (int y = 0; y < tilemap.height; y++) {
        for (int x = 0; x < tilemap.width; x++) {
          float factor = noise.GetNoise(
            static_cast<float>((x + offsetX) * zoom), 
            static_cast<float>((y + offsetY) * zoom) 
          );
          int index = y * tilemap.width + x;

          Tile& tile = tilemap.map[index];

          if ((std::abs(centerX - x) < 5 && std::abs(centerY - y) < 5) || factor < 0.5) {
            tile.up = grass;
            tile.down = water;
            tile.needsAutoTiling = true;
          } else {
            tile.up = water;
            tile.needsAutoTiling = false;
            tile.isWalkable = false;
          }
        }
      }
   }

  private:
    SDL_Renderer* renderer;
};


class TilemapRenderSystem : public RenderSystem {
  public:
    void run(SDL_Renderer* renderer) {
      auto& tilemap = scene->world->get<TilemapComponent>();
      const auto c = scene->mainCamera->get<TransformComponent>();
      const auto cameraComponent = scene->mainCamera->get<CameraComponent>();
      const int z = cameraComponent.zoom;
      int size = tilemap.tileSize;

      int startX = std::max(0, c.x / (size * z));
      int endX = std::min(tilemap.width, (c.x + cameraComponent.viewportWidth) / (size * z));
      int startY = std::max(0, c.y / (size * z));
      int endY = std::min(tilemap.height, (c.y + cameraComponent.viewportHeight) / (size * z));


      for (int y = startY; y <= endY; y++) {
        for (int x = startX; x <= endX; x++) {
          Tile tile = tilemap.map[y * tilemap.width + x];

          int renderSize = tilemap.tileSize * z;

          if (tile.down.texture) {
            SDL_Rect downClip = {
              tile.down.x,
              tile.down.y,
              size,
              size
            };

            tile.down.texture->render(
              x * renderSize - c.x,
              y * renderSize - c.y,
              renderSize,
              renderSize,
              &downClip
            );
          }
          SDL_Rect upClip = {
              tile.up.x,
              tile.up.y,
              size,
              size
          };
          tile.up.texture->render(
            x * renderSize - c.x,
            y * renderSize - c.y,
            renderSize,
            renderSize,
            &upClip
          );
        }
      }
    }
};

std::map<u_int8_t, std::vector<std::pair<int, int>>> m = {
    {  2, {{   0,  80 }} },
    {  8, {{  48,  96 }} },
    { 10, {{  80, 112 }} },
    { 11, {{  48,  80 }} },
    { 16, {{   0,  96 }} },
    { 18, {{  64, 112 }} },
    { 22, {{  16,  80 }} },
    { 24, {{  16,  96 }, {  32,  96 }} },
    { 26, {{ 144,  32 }} },
    { 27, {{ 144,  80 }} },
    { 30, {{  96,  80 }} },
    { 31, {{  32,  80 }} },
    { 64, {{   0,  32 }} },
    { 66, {{   0,  48 }, {   0,  64 }} },
    { 72, {{  80,  96 }} },
    { 74, {{ 128,  32 }} },
    { 75, {{ 112,  80 }} },
    { 80, {{  64,  96 }} },
    { 82, {{ 144,  48 }} },
    { 86, {{ 128,  80 }} },
    { 88, {{ 128,  48 }} },
    { 90, {{   0, 112 }, {  16, 112 }} },
    { 91, {{  32, 112 }} },
    { 94, {{  96,  48 }} },
    { 95, {{  96, 112 }} },
    {104, {{  48,  48 }} },
    {106, {{ 144,  64 }} },
    {107, {{  48,  64 }} },
    {120, {{ 112,  64 }} },
    {122, {{  48, 112 }} },
    {123, {{ 112, 112 }} },
    {126, {{  48, 112 }} },
    {127, {{  64,  64 }} },
    {208, {{  16,  48 }} },
    {210, {{  96,  64 }} },
    {214, {{  16,  64 }} },
    {216, {{ 128,  64 }} },
    {218, {{  96,  32 }} },
    {219, {{  32, 112 }} },
    {222, {{  96,  96 }} },
    {223, {{  80,  64 }} },
    {248, {{  32,  48 }} },
    {250, {{ 112,  96 }} },
    {251, {{  64,  80 }} },
    {254, {{  80,  80 }} },
    {255, {
            {   0,   0 }, {  16,   0 }, {  32,   0 }, {  48,   0 }, {  64,   0 }, {  80,   0 },
            {   0,  16 }, {  16,  16 }, {  32,  16 }, {  48,  16 }, {  64,  16 }, {  80,  16 },
            {  32,  64 }
          }
    },
    {  0, {
            { 16,  32 }, {  32,  32 }, {  48,  32 },
            { 64,  32 }, {  80,  32 }, {  64,  48 }, {  80,  48 }
          }
    }
};


const int dx[8] = { -1,  0,  1, -1, 1, -1, 0, 1 }; 
const int dy[8] = { -1, -1, -1,  0, 0,  1, 1, 1 };

std::map<u_int8_t, std::pair<int, int>> d_corner = {
  {0, {  1,  1 }},
  {2, { -1,  1 }},
  {5, {  1, -1 }},
  {7, { -1, -1 }},
};

class AutoTilingSetupSystem : public SetupSystem {
public:
  void run() {
    auto& tilemapComponent = scene->world->get<TilemapComponent>();
    int width = tilemapComponent.width;
    int height = tilemapComponent.height;
    int size = tilemapComponent.tileSize;
    // Loop through each tile in the tilemap
    for (int y = 0; y < tilemapComponent.height; y++) {
      for (int x = 0; x < tilemapComponent.width; x++) {
        int index = y * width + x;
        auto& tilemap = tilemapComponent.map;
        Tile& tile = tilemap[index];

        if (!tile.needsAutoTiling)
          continue;


        uint8_t surrounding = 0;
        // Loop through each of the eight directions
        for (int i = 0; i < 8; i++) {
          // Calculate the coordinates of the neighboring tile
          int nx = x + dx[i];
          int ny = y + dy[i];

          // Check if the coordinates are out of bounds
          if (nx < 0 || nx >= width || ny < 0 || ny >= height) {
            continue;  // If out of bounds, skip this iteration
          }

          // For corner tiles, check the two adjacent cardinal directions
          if (i == 0 || i == 2 || i == 5 || i == 7) {  // i is 0, 2, 5, 7 for corner tiles
            int nx1 = nx + d_corner[i].first; 
            int ny1 = ny + 0;  // This is for legibility
            int nx2 = nx + 0;
            int ny2 = ny + d_corner[i].second;

            // If either of the cardinal tiles are missing, skip this iteration
            if (nx1 < 0 || nx1 >= width || ny1 < 0 || ny1 >= height || 
              nx2 < 0 || nx2 >= width || ny2 < 0 || ny2 >= height) {
              continue;
            }

            if (tilemap[ny1 * width + nx1].up.texture != tilemap[ny * width + nx].up.texture || 
              tilemap[ny2 * width + nx2].up.texture != tilemap[ny * width + nx].up.texture)
            {
              continue;
            }
          }

          int neighborIndex = ny * width + nx;
          // Get the Tile of the neighboring tile
          const Tile& neighborTile = tilemap[neighborIndex];
          if (tile.up.texture == neighborTile.up.texture) {
            surrounding |= 1 << i;          
          } 
        }
        auto iter = m.find(surrounding);

        if (iter == m.end()) {
          tile.up.x = 0;
          tile.up.y = 0;
          print("Tile not found", static_cast<int>(surrounding));
          exit(1);
        } else {
          auto& pairs = iter->second;

          if (pairs.size() == 1) {
            tile.up.x = pairs[0].first;
            tile.up.y = pairs[0].second;
          } else {
            int index = rand() % pairs.size();
            tile.up.x = pairs[index].first;
            tile.up.y = pairs[index].second;
          }
        }
      }
    }
  } 
};

class WorldSetupSystem : public SetupSystem {
  public:
    void run() {
      int tilemapWidth = 50;
      int tilemapHeight = 38;
      int tilemapTileSize = 16;

      scene->world = new Entity(scene->r.create(), scene);
      scene->world->addComponent<TilemapComponent>(tilemapWidth, tilemapHeight, tilemapTileSize);
      scene->world->addComponent<WorldComponent>(tilemapWidth * tilemapTileSize, tilemapHeight*tilemapTileSize);
    }
};

class CameraSetupSystem : public SetupSystem {
  public:
    void run() {
      const auto worldComponent = scene->world->get<WorldComponent>();
      
      int cameraWidth = 800;
      int cameraHeight = 600;
      int x = worldComponent.width / 2 - cameraWidth / 2;
      int y = worldComponent.height / 2 - cameraHeight / 2;
      float zoom = 5;

      scene->mainCamera = new Entity(scene->r.create(), scene);
      scene->mainCamera->addComponent<TransformComponent>(x, y);
      scene->mainCamera->addComponent<CameraComponent>(cameraWidth, cameraHeight, zoom);
    }
};

class PlayerSetupSystem : public SetupSystem {
  public:
    void run() {
      const auto worldComponent = scene->world->get<WorldComponent>();
      const auto cameraComponent = scene->mainCamera->get<CameraComponent>();
      int spriteSize = 48;
      int x = worldComponent.width / 2 - (spriteSize * cameraComponent.zoom) / 2;
      int y = worldComponent.height / 2 - (spriteSize * cameraComponent.zoom) / 2;
 
      scene->player = new Entity(scene->r.create(), scene);
      scene->player->addComponent<TransformComponent>(x, y);
      auto& s = scene->player->addComponent<SpriteComponent>(
        "Sprites/Cat/SpriteSheet.png",
        0, 0,
        spriteSize,
        8,
        1000
      );
      s.lastUpdate = SDL_GetTicks();
      scene->player->addComponent<ColliderComponent>(19, 22, 10, 10, SDL_Color{200, 0, 200});
    }
};

class PlayerSpriteUpdateSystem : public UpdateSystem {
public:
  void run(float dT) {
    const auto playerSpeed = scene->player->get<SpeedComponent>();
    auto& playerSprite = scene->player->get<SpriteComponent>();

    if (playerSpeed.x < 0) {
      playerSprite.yIndex = 7;
    }
    else if (playerSpeed.x > 0) {
      playerSprite.yIndex = 6;
    }
    else if (playerSpeed.y < 0) {
      playerSprite.yIndex = 5;
    }
    else if (playerSpeed.y > 0) {
      playerSprite.yIndex = 4;
    } else {
      if (playerSprite.yIndex == 7) {
        playerSprite.yIndex = 2;
      } else if (playerSprite.yIndex == 6) {
        playerSprite.yIndex = 3;
      } else if (playerSprite.yIndex == 5) {
        playerSprite.yIndex = 1;
      } else if (playerSprite.yIndex == 4) {
        playerSprite.yIndex = 0;
      }
    }

  }
};

class CameraFollowUpdateSystem : public UpdateSystem {
public:
  void run(float dT) {
    auto& cameraPosition = scene->mainCamera->get<TransformComponent>();
    const auto cameraComponent = scene->mainCamera->get<CameraComponent>();
    const auto playerPosition = scene->player->get<TransformComponent>();
    const auto worldComponent = scene->world->get<WorldComponent>();
    const int spriteSize = scene->player->get<SpriteComponent>().size * cameraComponent.zoom;

    int px = playerPosition.x - cameraComponent.viewportWidth/2 + spriteSize/2;
    int py = playerPosition.y - cameraComponent.viewportHeight/2 + spriteSize/2;

    if (px > 0 && px < worldComponent.width) {
      cameraPosition.x = px;
    }
    if (py > 0 && py < worldComponent.height) {
      cameraPosition.y = py;
    }
  }
};

class ColliderRenderSystem : public RenderSystem {
public:
  void run(SDL_Renderer* r) {
    auto view = scene->r.view<TransformComponent, ColliderComponent>();
    const auto c = scene->mainCamera->get<TransformComponent>();
    const auto z = scene->mainCamera->get<CameraComponent>().zoom;

    for(auto entity : view) {
      const auto colliderComponent = view.get<ColliderComponent>(entity);
      const auto transformComponent = view.get<TransformComponent>(entity);

      SDL_Rect col {
        static_cast<int>(transformComponent.x + colliderComponent.xo * z - c.x),
        static_cast<int>(transformComponent.y + colliderComponent.yo * z - c.y),
        static_cast<int>(colliderComponent.w * z),
        static_cast<int>(colliderComponent.h * z)
      };
      SDL_SetRenderDrawColor(r, colliderComponent.color.r, colliderComponent.color.g, colliderComponent.color.b, 200);
      SDL_RenderDrawRect(r, &col);
    }
  }
};

class TileColliderRenderSystem : public RenderSystem {
public:
  void run(SDL_Renderer* r) {
    const auto tilemap = scene->world->get<TilemapComponent>();
    const int width = tilemap.width;
    const int height = tilemap.height;
    const int size = tilemap.tileSize;
    const auto c = scene->mainCamera->get<TransformComponent>();
    const auto cameraComponent = scene->mainCamera->get<CameraComponent>();
    const int z = cameraComponent.zoom;
    
    int startX = std::max(0, c.x / (size * z));
    int endX = std::min(width, (c.x + cameraComponent.viewportWidth) / (size * z));
    int startY = std::max(0, c.y / (size * z));
    int endY = std::min(height, (c.y + cameraComponent.viewportHeight) / (size * z));

    SDL_SetRenderDrawColor(r, 0, 0, 255, 255); 

    for (int y = startY; y <= endY; y++) {
      for (int x = startX; x <= endX; x++) {
        Tile tile = tilemap.map[y * tilemap.width + x];
        SDL_Rect col {
          static_cast<int>(x * size * z - c.x),
          static_cast<int>(y * size * z - c.y),
          static_cast<int>(size * z),
          static_cast<int>(size * z)
        };
        if (!tile.isWalkable) {
          SDL_RenderFillRect(r, &col);
        }
      }
    }
  }
};

class TileCollisionUpdateSystem : public UpdateSystem {
  public:
    void run(float dT) {
      const auto playerPosition = scene->player->get<TransformComponent>();
      const auto playerCollider = scene->player->get<ColliderComponent>();
      const auto world = scene->world->get<WorldComponent>();
      const auto cameraZoom = scene->mainCamera->get<CameraComponent>().zoom;
      auto& playerMovement = scene->player->get<SpeedComponent>();

      const auto tilemapComponent = scene->world->get<TilemapComponent>();
      const int tileSize = tilemapComponent.tileSize * cameraZoom;

      if (playerMovement.x == 0 && playerMovement.y == 0) {
        return;
      }

      const int colliderPositionX = playerPosition.x + playerCollider.xo * cameraZoom;
      const int colliderPositionY = playerPosition.y + playerCollider.yo * cameraZoom;
      const int colliderSize = playerCollider.w * cameraZoom;

      const int futureX = colliderPositionX + playerMovement.x * dT;
      const int futureY = colliderPositionY + playerMovement.y * dT;
      const int futureRightX = futureX + colliderSize;
      const int futureBottomY = futureY + colliderSize;

      if (futureX <= 0 || futureY <= 0 || futureRightX >= world.width * cameraZoom || futureBottomY >= world.height * cameraZoom) {
        playerMovement.x = 0;
        playerMovement.y = 0;
      }

      

    // Convert the future positions from pixels to tile coordinates.
    std::vector<std::pair<int, int>> futureTiles = {
        {futureX / tileSize, futureY / tileSize}, // top left corner
        {futureRightX / tileSize, futureY / tileSize}, // top right corner
        {futureX / tileSize, futureBottomY / tileSize}, // bottom left corner
        {futureRightX / tileSize, futureBottomY / tileSize}  // bottom right corner
    };

    for (const auto& [tileX, tileY] : futureTiles) {
        // Get the tile at the future position.
        const Tile& tile = tilemapComponent.map[tileY * tilemapComponent.width + tileX];

        // If the tile is not walkable, set the speed to 0.
        if (!tile.isWalkable) {
            playerMovement.x = 0;
            playerMovement.y = 0;
            return;
        }
    }
  }
};



