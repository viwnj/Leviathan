#include <iostream>
#include "Layer.h"
#include "Components/BoxCollider.h"
#include "LayerManager.h"

void Layer::Render(SDL_Renderer* renderer) {
	for (auto entity : entityStack) {
		entity->Render(renderer);
	}
}

void Layer::Update(float deltaTime) {
	for (int i = 0; i < entityStack.size(); i++) {
		if (!entityStack[i]->isActive) {
			entityMap.erase(entityStack[i]->name);
			entityStack.erase(entityStack.begin() + i);
			manager->GetCollidableEntities();
		}
		else {
			entityStack[i]->Update(deltaTime);
		}
	}
}

void Layer::AddEntity(Entity* entity) {
	entityMap.emplace(entity->name, entity);
	entityStack.emplace_back(entity);

	if (entity->HasComponent<BoxCollider>()) {
		manager->GetCollidableEntities();
	}
}

std::vector<Entity*> Layer::GetAllEntities() {
	return entityStack;
}

Entity* Layer::GetEntity(std::string eId) {
	return entityMap[eId];
}
