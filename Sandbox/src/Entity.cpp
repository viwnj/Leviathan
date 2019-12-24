#include "Entity.h"
#include <iostream>


void Entity::Render(SDL_Renderer* renderer) {
	for (auto component : componentStack) {
		component->Render(renderer);
	}
}

void Entity::Update(float deltaTime) {
	for (auto component : componentStack) {
		component->Update(deltaTime);
	}
}

void Entity::ListAllComponents() {
	for (auto const& component : componentTypeMap) {
		std::cout << component.first->name() << std::endl;
	}
}