#include "Collision.h"
#include <iostream>

// https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection
bool Collision::CheckRectCollision(const SDL_Rect& rectA, const SDL_Rect& rectB){
	return (
		rectA.x + rectA.w >= rectB.x &&
		rectB.x + rectB.w >= rectA.x &&
		rectA.y + rectA.h >= rectB.y &&
		rectB.y + rectB.h >= rectA.y
		);
}
