#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <string>
#include "Transform.h"
#include "../Component.h"
#include  "../Collision.h"
#include "../Camera.h"

class BoxCollider : public Component {
	public:
		std::string colliderTag;
		SDL_Rect collider;
		SDL_Rect srcRect;
		SDL_Rect destRect;
		Transform* transform;
		bool showDebugUI;

		BoxCollider(std::string colliderTag, int x, int y, int width, int height, bool showDebugUI) {
			this->colliderTag = colliderTag;
			this->collider = {
				x,
				y,
				width,
				height
			};

			this->showDebugUI = showDebugUI;
		}

		void Initialize() override {
			if (owner->HasComponent<Transform>()) {
				this->transform = owner->GetComponent<Transform>();
				this->srcRect = { 0, 0, transform->width, transform->height };
				this->destRect = { collider.x, collider.y, collider.w, collider.h };
			}
		}

		void Update(float deltaTime) override {
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
			destRect.x = collider.x - Camera::source.x;
			destRect.y = collider.y - Camera::source.y;

		}

		void Render(SDL_Renderer* renderer) override {
			if (showDebugUI) {
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
				SDL_RenderDrawRect(renderer, &destRect);
			}
		}
};

#endif