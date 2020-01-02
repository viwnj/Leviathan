#ifndef SANDBOXAPP_H
#define SANDBOXAPP_H

#include <string>
#include <vector>
#include <iostream>
#include <sol.hpp>
#include "Color.h"
#include "LayerManager.h"
#include "Map.h"
#include "Layer.h"
#include "Entity.h"
#include "Application.h"
#include "AssetManager.h"
#include "Camera.h"
#include "Components/Transform.h"
#include "Components/Sprite.h"
#include "Components/KeyboardControl.h"
#include "Components/Label.h"
#include "Components/ProjectileEmitter.h"

class SandboxApp : public Application {
	
	public:
		Map* map;
		LayerManager* layerManager = new LayerManager();
		Entity* CameraAttachedEntity;
		SandboxApp();
		const unsigned int FPS = 60;
		const unsigned int FRAME_TARGET_TIME = 1000 / FPS;
		const unsigned int WINDOW_WIDTH = 800;
		const unsigned int WINDOW_HEIGHT = 600;

		void LoadLevel(int level);
		void Render();
		void Update();
		void HandleCameraMovement();
		void ProcessInput();
		void Run();
		void CheckCollisions();

};

#endif