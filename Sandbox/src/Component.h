#ifndef COMPONENT_H
#define COMPONENT_H
#include "AssetManager.h"


class Entity;
class Component {
public:
  Entity* owner;
  virtual ~Component() {}
  virtual void Initialize() {}
  virtual void Update(float deltaTime) {}
  virtual void Render(SDL_Renderer* renderer) {
  }
};

#endif