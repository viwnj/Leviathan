#pragma once
#include <glm/glm.hpp>
#include "../Component.h"

class Transform : public Component {
	public: 
		glm::vec2 position;
		glm::vec2 velocity;
		int width;
		int height;
		int scale;

		Transform(int posX, int posY, int velX, int velY, int w, int h, int s) {
			position = glm::vec2(posX, posY);
			velocity = glm::vec2(velX, velY);
			this->width = w;
			this->height = h;
			scale = s;
		}

		void Initialize() override
		{
		}

		void Update(float deltaTime) override
		{
			position.x += velocity.x * deltaTime;
			position.y += velocity.y * deltaTime;
		}

		void Render(SDL_Renderer* renderer) override {
		};
};