#pragma once
#include <vector>
#include <SDL.h>
#include "Entity.h"

class Layer {
	public:
		std::vector<Entity*> entityStack;
		void Update(float deltaTime);
		void Render(SDL_Renderer* renderer);
		void AddEntity(Entity* entity);
};
