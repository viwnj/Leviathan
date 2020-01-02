#include "LayerManager.h"

void LayerManager::AddLayer(Layer* layer) {
	layerMap.emplace(layer->layerId, layer);
	layerStack.emplace_back(layer);
}

Layer* LayerManager::GetLayer(std::string layerName) {
	return layerMap[layerName];
}


void LayerManager::GetCollidableEntities() {
	collidableEntities.clear();
	for (auto const& layer : layerStack) {
		for (auto const& entity : layer->GetAllEntities()) {
			if (entity->HasComponent<BoxCollider>()) {
				collidableEntities.emplace_back(entity);
			}
		}
	}
}

void LayerManager::HideLayer(std::string layerName) {
	// TODO: Hide layer
}

CollisionType LayerManager::CheckEntityCollisions() {	
	std::map<Entity*, Entity*> collisionCheckedMap;
	for (auto& thisEntity : collidableEntities) {
		BoxCollider* thisCollider = thisEntity->GetComponent<BoxCollider>();
		for (auto& thatEntity: collidableEntities) {
			if (collisionCheckedMap.size() > 0 && collisionCheckedMap[thatEntity] == thisEntity) continue; // Prevents checking : A-B then B-A
			if (thisEntity->name.compare(thatEntity->name) == 0) continue;
			BoxCollider* thatCollider = thatEntity->GetComponent<BoxCollider>();
			if (Collision::CheckRectCollision(thisCollider->collider, thatCollider->collider)) {
				// Collision detected, do something with it.
				thatEntity->OnCollision(thisCollider->colliderTag, thatCollider->colliderTag);
			}
			collisionCheckedMap.emplace(thisEntity, thatEntity);
		}
	}

	collisionCheckedMap.clear();
	return NO_COLLISION;
}


void LayerManager::Render(SDL_Renderer* renderer) {
	for (auto& layer : layerStack) {
		layer->Render(renderer);
	}
}


void LayerManager::Update(float deltaTime) {
	for (auto& layer : layerStack) {
		layer->Update(deltaTime);
	}
}