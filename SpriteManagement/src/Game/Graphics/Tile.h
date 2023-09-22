#pragma once
#include "Game/Graphics/Texture.h"

struct Terrain {
  Texture* texture = nullptr;
  int x = 0;
  int y = 0;
};

struct Tile {
  Terrain up;
  Terrain down;
  bool needsAutoTiling;
  bool isWalkable = true;
};

