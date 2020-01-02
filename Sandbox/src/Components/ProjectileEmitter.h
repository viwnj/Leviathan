#ifndef PROJECTILE_EMMITER_H
#define PROJECTILE_EMMITER_H

#include <glm/glm.hpp>
#include "Transform.h"
#include "../Component.h"

class ProjectileEmmiter : public Component {
	private:
		Transform* transform;
		glm::vec2 origin;
		int speed;
		int range;
		float angleRad;
		bool shouldLoop;
	public:
		ProjectileEmmiter(int speed, int angleDeg, int range, bool shouldLoop) {
			this->speed = speed;
			this->range = range;
			this->shouldLoop = shouldLoop;
			this->angleRad = glm::radians(static_cast<float>(angleDeg));
		}

		void Initialize() override {
			transform = owner->GetComponent<Transform>();
			origin = glm::vec2(transform->position.x, transform->position.y);
			// Transform an angle and a distance back to X and Y (polar coordinates to cartesian coordinates?)
			transform->velocity = glm::vec2(glm::cos(angleRad) * speed, glm::sin(angleRad) * speed);
		}

		void Update(float deltaTime) override {
			if (glm::distance(transform->position, origin) > range) {
				if (shouldLoop) {
					transform->position.x = origin.x;
					transform->position.y = origin.y;
				} else {
					owner->Destroy();
				}
			}
		}
};

#endif