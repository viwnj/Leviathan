#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Renderer.h"

class Texture
{
	public:
		static SDL_Texture* LoadTexture(const char* fileName);
		static void Draw(SDL_Texture* texture, SDL_Rect sourceRect, SDL_Rect destRect, SDL_RendererFlip flip);
};

#endif