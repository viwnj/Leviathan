#pragma once
#include <Levi.h>
#include <string>
#include <vector>
#include <iostream>
#include "Layer.h"
#include "Entity.h"
#include "AssetManager.h"
#include "Components/Transform.h"
#include "Components/Sprite.h"

class SandboxApp : public Leviathan::Application {
	
	public:

		AssetManager* assetManager = new AssetManager(); // Here's where we're storing all our assets
		SandboxApp() {
			this->LoadLevel();
		}
		const unsigned int FPS = 60;
		const unsigned int FRAME_TARGET_TIME = 1000 / FPS;
		std::vector<Layer*> layerStack;

		void LoadLevel() {
			assetManager->AddTexture("chopper", std::string(".\\src\\assets\\images\\chopper-spritesheet.png").c_str(), renderer);
			//assetManager->AddTexture("tank", std::string(".\\src\\assets\\images\\tank-big-right.png").c_str(), renderer);

			SDL_Texture* chopperTexture = assetManager->GetTexture("chopper");

			Layer* testLayer = new Layer();
			// Start adding game entities/components
			Entity* testEntity = new Entity();
			testEntity->AddComponent<Transform>(50, 50, 10, 10, 32, 32, 1);
			testEntity->AddComponent<Sprite>(chopperTexture);
			
			/*
				Entity* tankEntity = new Entity();
				tankEntity->AddComponent<Transform>(30, 250, 10, 10, 32, 32, 1);
				tankEntity->AddComponent<Sprite>(assetManager->GetTexture("tank"));
			*/

			testLayer->AddEntity(testEntity);
			layerStack.emplace_back(testLayer);
		}

		void Render() {
			SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
			SDL_RenderClear(renderer);
			for (auto layer : layerStack) {
				layer->Render(renderer);
			}
			SDL_RenderPresent(renderer);
		}

		void Update() {
			// Setting up a basic game loop, + clamping the deltaTime
			while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));

			float deltaTime = this->GetDeltaTime();

			for (auto layer : layerStack) {
				layer->Update(deltaTime);
			}
		}

		void ProcessInput() {
			SDL_Event winEvents;

			if (SDL_PollEvent(&winEvents)) {
				if (winEvents.type == SDL_QUIT) {
					this->Destroy();
				}
			}
		}

		void Run() {
			while (this->isActive) {
				this->ProcessInput();
				this->Render();
				this->Update();
			}
		}

};