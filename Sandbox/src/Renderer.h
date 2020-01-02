#pragma once
#include <SDL.h>

class Renderer {
	public:
		static SDL_Renderer* renderer;
		static void Init(SDL_Window* win) {
			renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL) {
				throw "The renderer could not be created";
			}
		}
};