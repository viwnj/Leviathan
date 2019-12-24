#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
class Texture
{
	public:
		static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* renderer);
		static void Draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect sourceRect, SDL_Rect destRect, SDL_RendererFlip flip);
};

