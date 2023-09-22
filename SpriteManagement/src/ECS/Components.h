#pragma once

#include <glm/glm.hpp>
#include <string>
#include "Game/Graphics/PixelShader.h"
#include "Game/Graphics/Texture.h"
#include "Game/Graphics/Tile.h"


struct NameComponent {
  std::string name;
};

struct TransformComponent {
  int x;
  int y;
};

struct SpeedComponent {
  int x;
  int y;
};

struct SpriteComponent {
  std::string name;
  int xIndex = 0;
  int yIndex = 0;
  int size = 48;
  int animationFrames = 0;
  int animationDuration = 0;
  PixelShader shader = { nullptr, "" };

  Uint32 lastUpdate = 0;
};

struct TilemapComponent {
  int width;
  int height;
  int tileSize;
  std::vector<Tile> map;
};

struct CameraComponent {
  int viewportWidth;
  int viewportHeight;
  float zoom;
};

struct WorldComponent {
  int width;
  int height;
};

struct ColliderComponent {
  int xo;
  int yo;
  int w;
  int h;
  SDL_Color color = {255, 255, 255};
};


