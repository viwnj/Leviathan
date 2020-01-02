#ifndef  LAYERMANAGER_H
#define LAYER_MANAGER_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Constants.h"
#include "Layer.h"
#include "Entity.h"
#include "Components/BoxCollider.h"

class LayerManager {
private:
	bool isHidden;
	std::map<std::string, Layer*> layerMap;
	std::vector<Layer*> layerStack;
	std::vector<Entity*> collidableEntities;
public:
	void AddLayer(Layer* layer);
	CollisionType CheckEntityCollisions();
	Layer* GetLayer(std::string layerName);
	void HideLayer(std::string layerName);
	void Render(SDL_Renderer* renderer);
	void Update(float deltaTime);
	void GetCollidableEntities();
};

#endif // ! LAYERMANAGER_H

