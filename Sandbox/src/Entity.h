#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include <sol.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <typeinfo>
#include <string>
#include <vector>
#include <thread>
#include <map>
#include "Component.h"
class Layer;
class Entity
{
	private:
	public:
		sol::state lua;
		sol::function update;
		std::vector<Component*> componentStack;
		std::string scriptFile;
		Layer* ownerLayer;
		std::map<const std::type_info*, Component*> componentTypeMap;
		std::string name;
		bool isActive;
		int angle = 90; //deg

		Entity(std::string name) {
			this->name = name;
			this->isActive = true;
		}
		
		void Render(SDL_Renderer* renderer);
		void Update(float deltaTime);
		void OnCollision(std::string thisColliderTag, std::string thatColliderTag);
		void Destroy();
		void AttachScriptFile(std::string scriptFile);
		template <typename T, typename... TArgs>
		void AddComponent(TArgs&& ...args) {
			T* newComponent = new T(std::forward<TArgs>(args)...);
			newComponent->owner = this;
			componentStack.emplace_back(newComponent);
			componentTypeMap[&typeid(*newComponent)] = newComponent;
			newComponent->Initialize();
		};

		template <typename T>
		bool HasComponent() const {
			return componentTypeMap.count(&typeid(T));
		}

		template <typename T>
		T* GetComponent() {
			return static_cast<T*>(componentTypeMap[&typeid(T)]);
		}

		void ListAllComponents();
};

#endif