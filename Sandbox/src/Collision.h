#pragma once
#include <SDL.h>

class Collision {
	public:
		static bool CheckRectCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);
};