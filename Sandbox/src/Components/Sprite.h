#pragma once
#include <string>
#include <SDL.h>
#include <iostream>
#include "Transform.h"
#include "../Texture.h"
#include "../Component.h"
#include "../Texture.h"

class Sprite : public Component {
	private:
    int numFramesPerRow = 2;
    int animationSpeed = 100; // do animation every 25~ frames
    int frameCount = 0;
    int currentFrame = 0;
    Transform* transform;
		SDL_Rect sourceRect;
		SDL_Rect destRect;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		SDL_Texture* texture;
	public:
		Sprite(SDL_Texture* texture) {
      //int w, h;
      //std::cout << "isTexture:" << SDL_QueryTexture(texture, NULL, NULL, &w, &h) << std::endl;
			SetTexture(texture);
		}

		void SetTexture(SDL_Texture* tx) {
			this->texture = tx;
		}

    void Initialize() override
    {
      transform = owner->GetComponent<Transform>();
      sourceRect.x = 0;
      sourceRect.y = 0;
      sourceRect.w = transform->width;
      sourceRect.h = transform->height;
    }



    void Update(float deltaTime) override
    {

      // Cycle through numFrames and 0 everytime GetTicks is divisible by animationSpeed
      // This makes our animation really smooth!
        sourceRect.x = sourceRect.w * static_cast<int>(SDL_GetTicks() / animationSpeed % numFramesPerRow);

      destRect.x = static_cast<int>(transform->position.x);
      destRect.y = static_cast<int>(transform->position.y);
      destRect.w = 32;
    	destRect.h = 32;
    }

    void Render(SDL_Renderer* renderer) override
    {
      Texture::Draw(renderer, texture, sourceRect, destRect, flip);
    }
};