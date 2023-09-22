#pragma once
#include <string>
#include <functional>
#include <SDL.h>

struct PixelShader {
    std::function<Uint32(Uint32)> func;
    std::string name;
};
