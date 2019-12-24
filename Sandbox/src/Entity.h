#pragma once
#include <SDL.h>
#include <iostream>
#include <glm/glm.hpp>
#include <typeinfo>
#include <string>
#include <vector>
#include <map>
#include "Component.h"

class Entity
{
	public:
		std::vector<Component*> componentStack;
		std::map<const std::type_info*, Component*> componentTypeMap;

		void Render(SDL_Renderer* renderer);
		void Update(float deltaTime);

		template <typename T, typename... TArgs>
		void AddComponent(TArgs&& ...args) {
			T* newComponent = new T(std::forward<TArgs>(args)...);
			newComponent->owner = this;
			componentStack.emplace_back(newComponent);
			componentTypeMap[&typeid(*newComponent)] = newComponent;
			newComponent->Initialize();
		};

		template <typename T>
		T* GetComponent() {
			return static_cast<T*>(componentTypeMap[&typeid(T)]);
		}

		void ListAllComponents();
};

