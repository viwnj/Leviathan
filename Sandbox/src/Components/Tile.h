#ifndef TILE_H
#define TILE_H
#include <SDL.h>
#include <iostream>
#include <glm/glm.hpp>
#include "../Texture.h"
#include "../Component.h"
#include "../Camera.h"

class Tile : public Component {
	public:
		SDL_Texture* texture;
		SDL_Rect srcRect;
		SDL_Rect destRect;
		glm::vec2 position;

		Tile(SDL_Texture* texture, int srcRectX, int srcRectY, int x, int y, int tileSize, int tileScale) {
			this->texture = texture;
			srcRect.x = srcRectX;
			srcRect.y = srcRectY;
			srcRect.w = tileSize;
			srcRect.h = tileSize;

			destRect.x = x;
			destRect.y = y;
			destRect.w = tileSize * tileScale;
			destRect.h = tileSize * tileScale;

			position.x = static_cast<float>(x);
			position.y = static_cast<float>(y);
		}
		~Tile() {
			SDL_DestroyTexture(texture);
		}

		void Update(float deltaTime) override {
			destRect.x = static_cast<int>(position.x) - Camera::source.x;
			destRect.y = static_cast<int>(position.y) - Camera::source.y;
		}

		void Render(SDL_Renderer* renderer) override {
			Texture::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
		}
};

#endif