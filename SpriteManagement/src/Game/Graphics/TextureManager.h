#pragma once
#include <map>
#include <string>
#include "Texture.h"
#include "PixelShader.h"

class TextureManager {
  public:
    static Texture* LoadTexture(
      const std::string& filename,
      SDL_Renderer* renderer,
      PixelShader shader = { nullptr, "" }
    );
    static void UnloadTexture(const std::string& filename, const std::string& shadername = "");
    static Texture* GetTexture(const std::string& filename, const std::string& shadername = "");

  private:
    static std::map<std::string, Texture*> textures;
};
