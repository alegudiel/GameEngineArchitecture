#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <functional>
#include "PixelShader.h"

class Texture {
	public:
		Texture(SDL_Renderer* renderer);
		~Texture();

		void load(std::string path, PixelShader shader = { nullptr, "" });

		void render(int x, int y, int w = 0, int h = 0, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

		Uint32 color(Uint8 red, Uint8 green, Uint8 blue);

		bool lockTexture();
		bool unlockTexture();
		Uint32* getPixels();
    int getPixelCount();
    Uint32 getPixel(int x, int y);
    Uint32 getPixel(int xy);

		int width;
		int height;
	private:
		SDL_Texture* texture;
		void* pixels;
		int pitch;
    Uint32 format;
    SDL_PixelFormat* mappingFormat;

    SDL_Renderer* renderer;
};