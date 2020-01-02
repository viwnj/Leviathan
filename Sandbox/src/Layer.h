#ifndef LAYER_H
#define LAYER_H
#include <vector>
#include <map>
#include <SDL.h>
#include "Entity.h"

class LayerManager;
class Layer {
	private:
		std::vector<Entity*> entityStack;
		std::map<std::string, Entity*> entityMap;
	public:
		LayerManager* manager;
		std::string layerId;
		Layer(std::string layerId) {
			this->layerId = layerId;
		}

		void Update(float deltaTime);
		void Render(SDL_Renderer* renderer);
		Entity* GetEntity(std::string eId);
		std::vector<Entity*> GetAllEntities();
		void AddEntity(Entity* entity);
};

#endif