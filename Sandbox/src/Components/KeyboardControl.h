#ifndef KEYBOARDCONTROL_H
#define KEYBOARDCONTROL_H

#include <string>
#include <iostream>
#include "../Application.h"
#include "../Component.h"
#include "Sprite.h"
#include "Transform.h"
#include "../Entity.h"
#include "ProjectileEmitter.h"
#include "../Layer.h"
class KeyboardControl : public Component {
  public:
	  std::string upKey;
	  std::string rightKey;
	  std::string downKey;
	  std::string leftKey;
    std::string shootKey;
	  Transform* transform;
    Sprite* sprite;

    KeyboardControl(std::string upKey, std::string rightKey, std::string downKey, std::string leftKey, std::string shootKey)
    {
      this->upKey = GetSDLKeyStringCode(upKey);
      this->rightKey = GetSDLKeyStringCode(rightKey);
      this->downKey = GetSDLKeyStringCode(downKey);
      this->leftKey = GetSDLKeyStringCode(leftKey);
      this->shootKey = GetSDLKeyStringCode(shootKey);
    }

    std::string GetSDLKeyStringCode(std::string key)
    {
      if (key.compare("ArrowUp") == 0)
        return "1073741906";
      if (key.compare("ArrowRight") == 0)
        return "1073741903";
      if (key.compare("ArrowDown") == 0)
        return "1073741905";
      if (key.compare("ArrowLeft") == 0)
        return "1073741904";
      if (key.compare("space") == 0)
        return "32";

      return std::to_string(static_cast<int>(key[0]));
    }

    void Initialize() override {
      transform = owner->GetComponent<Transform>();
      sprite = owner->GetComponent<Sprite>();
    }

    void Update(float deltaTime) override {

      if (Application::event.type == SDL_KEYDOWN)
      {
        std::string keyCode = std::to_string(Application::event.key.keysym.sym);
        if (keyCode.compare(upKey) == 0)
        {

          transform->velocity.y = -100;
          transform->velocity.x = 0;
          owner->angle = 270;
          if (sprite) {
            sprite->Play("UpAnimation");
          }
        }
        if (keyCode.compare(rightKey) == 0)
        {

          transform->velocity.y = 0;
          transform->velocity.x = 100;
          owner->angle = 0;
          if (sprite) {
            sprite->Play("RightAnimation");
          }
        }
        if (keyCode.compare(downKey) == 0)
        {
          transform->velocity.y = 100;
          transform->velocity.x = 0;
          owner->angle = 90;

          if (sprite) {
            sprite->Play("DownAnimation");
          }
        }
        if (keyCode.compare(leftKey) == 0)
        {
          transform->velocity.y = 0;
          transform->velocity.x = -100;
          owner->angle = 180;
          if (sprite) {
            sprite->Play("LeftAnimation");
          }
        }
        if (keyCode.compare(shootKey) == 0)
        {
          Transform* ownerTransform = owner->GetComponent<Transform>();
          Entity* projectile = new Entity("projectile");
          projectile->AddComponent<Transform>(
            static_cast<int>(ownerTransform->position.x + ownerTransform->width / 2), 
            static_cast<int>(ownerTransform->position.y + ownerTransform->height / 2 ), 0, 0, 4, 4, 1);
          projectile->AddComponent<Sprite>("projectile-image");
          projectile->AddComponent<BoxCollider>("FRIENDLY_PROJECTILE", 
            static_cast<int>(ownerTransform->position.x + ownerTransform->width / 2), 
            static_cast<int>(ownerTransform->position.y + ownerTransform->height / 2), 4, 4, true);
          projectile->AddComponent<ProjectileEmmiter>(150, owner->angle, 200, false);
          owner->ownerLayer->AddEntity(projectile);
        }
      }

      if (Application::event.type == SDL_KEYUP)
      {
        std::string keyCode = std::to_string(Application::event.key.keysym.sym);
        if (keyCode.compare(upKey) == 0)
        {
          transform->velocity.y = 0;
        }
        if (keyCode.compare(rightKey) == 0)
        {
          transform->velocity.x = 0;
        }
        if (keyCode.compare(downKey) == 0)
        {
          transform->velocity.y = 0;
        }
        if (keyCode.compare(leftKey) == 0)
        {
          transform->velocity.x = 0;
        }
        if (keyCode.compare(shootKey) == 0)
        {
          std::cout << "..." << std::endl;
        }
      }
    }

};

#endif