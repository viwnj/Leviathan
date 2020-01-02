#pragma once
#include <SDL_ttf.h>
class Font {
	public:
		static TTF_Font* LoadFont(const char* fileName, int fontSize);
		static void Draw(SDL_Texture* tex, SDL_Rect pos);
};