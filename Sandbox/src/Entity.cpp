#include "Entity.h"
#include "Components/BoxCollider.h"
#include "Components/Tile.h"
#include "Components/ProjectileEmitter.h"
#include "Components/Sprite.h"
#include "Components/ProjectileEmitter.h"
#include "Components/Label.h"
#include "Components/Transform.h"
#include "Components/KeyboardControl.h"
#include "Color.h"

void Entity::Render(SDL_Renderer* renderer) {
	for (auto component : componentStack) {
		component->Render(renderer);
	}
}

void Entity::AttachScriptFile(std::string scriptFile) {
	this->scriptFile = scriptFile;
	lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
	lua.set_function("rgba", [](unsigned int r, unsigned int g, unsigned int b, unsigned int a) -> SDL_Color {
		return Color::rgba(r, g, b, a);
	});

	lua.set_function("AddComponent", [this](std::string componentType, sol::table params) {
		if (componentType.compare("Transform") == 0) {

			int posX = params["posX"];
			int posY = params["posY"];
			int velX = params["velX"];
			int velY = params["velY"];
			int	width = params["width"];
			int height = params["height"];
			int scale = params["scale"];
			AddComponent<Transform>(posX, posY, velX, velY, width, height, scale);
		}

		if (componentType.compare("Sprite") == 0) {
			std::string textureId = params["textureId"];
			sol::optional<bool> isAnimated = params["isAnimated"];
			if (isAnimated) {
		
				std::string textureId = params["textureId"];
				int numFrames = params["numFrames"];
				int animationSpeed = params["animationSpeed"];
				bool hasDirections = params["hasDirections"];
				bool isFixed = params["isFixed"];
				AddComponent<Sprite>(textureId, numFrames, animationSpeed, hasDirections, isFixed);
			}
			else {
				AddComponent<Sprite>(textureId);
			}
		}

		if (componentType.compare("KeyboardControl") == 0) {
			std::string upKey = params["upKey"];
			std::string rightKey = params["rightKey"];
			std::string downKey = params["downKey"];
			std::string leftKey = params["leftKey"];
			std::string shootKey = params["shootKey"];
			AddComponent<KeyboardControl>(upKey, rightKey, downKey, leftKey, shootKey);
		}

		if (componentType.compare("BoxCollider") == 0) {
			std::string colliderTag = params["colliderTag"];
			int posX = params["posX"];
			int posY = params["posY"];
			int w = params["w"];
			int h = params["h"];
			sol::optional<bool> showDebugUI = params["showDebugUI"];
			AddComponent<BoxCollider>(colliderTag, posX, posX, w, h, showDebugUI ? showDebugUI.value() : false);
		}

		if (componentType.compare("Label") == 0) {
			std::string fontFamily = params["fontFamily"];
			SDL_Color color = params["color"];
			std::string text = params["text"];
			int posX = params["posX"];
			int posY = params["posY"];
			AddComponent<Label>(fontFamily, text, color, posX, posY);
		}
	});


	lua.script_file(scriptFile);
	sol::function start = lua["start"];
	start();

}


void Entity::OnCollision(std::string thisColliderTag, std::string thatColliderTag) {

	if (
		thisColliderTag.compare("FRIENDLY_PROJECTILE") == 0 && thatColliderTag.compare("PLAYER") == 0 ||
		thatColliderTag.compare("FRIENDLY_PROJECTILE") == 0 && thisColliderTag.compare("PLAYER") ==  0	
	) {
		return;
	}
	lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
	lua.script_file(".\\src\\assets\\scripts\\tank1.lua");
	sol::optional<sol::function> OnCollision = lua["OnCollision"];
	if (OnCollision) {
		sol::function fn = OnCollision.value();
		fn();
	}
}

 void Entity::Update(float deltaTime) {
	for (auto component : componentStack) {
		component->Update(deltaTime);
	}
}

void Entity::ListAllComponents() {
	for (auto const& component : componentTypeMap) {
		std::cout << component.first->name() << std::endl;
	}
}

void Entity::Destroy() {
	this->isActive = false;
}