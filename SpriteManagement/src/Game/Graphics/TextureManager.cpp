#include "TextureManager.h"

std::map<std::string, Texture*> TextureManager::textures;

Texture* TextureManager::LoadTexture(const std::string& filename, SDL_Renderer* renderer, PixelShader shader) {
  if (textures.count(filename + shader.name) > 0) {
    return textures[filename + shader.name];
  }

  Texture* texture = new Texture(renderer);
  texture->load("assets/" + filename, shader);

  textures[filename + shader.name] = texture;
  return texture;
}

void TextureManager::UnloadTexture(const std::string& filename, const std::string& shadername) {
  if (textures.count(filename + shadername) > 0) {
    delete textures[filename + shadername];
    textures.erase(filename + shadername);
  }
}

Texture* TextureManager::GetTexture(const std::string& filename, const std::string& shadername) {
  if (textures.count(filename + shadername) > 0) {
    return textures[filename + shadername];
  }
  return nullptr;
}