#include "Layer.h"


void Layer::Render(SDL_Renderer* renderer) {
	for (auto entity : entityStack) {
		entity->Render(renderer);
	}
}

void Layer::Update(float deltaTime) {
	for (auto entity : entityStack) {
		entity->Update(deltaTime);
	}
}

void Layer::AddEntity(Entity* entity) {
	entityStack.emplace_back(entity);
}