#pragma once
#include "Font.h"
#include "Renderer.h"

TTF_Font* Font::LoadFont(const char* fileName, int fontSize) {
	return TTF_OpenFont(fileName, fontSize);
}

void Font::Draw(SDL_Texture* texture, SDL_Rect position) {
	SDL_RenderCopy(Renderer::renderer, texture, NULL, &position);
}