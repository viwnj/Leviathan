#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <map>
#include <SDL.h>
#include "Transform.h"
#include "Animation.h"
#include "Texture.h"
#include "Component.h"
#include "Texture.h"#include "Camera.h"
class Sprite : public Component {
	private:
    bool isAnimated;
    bool isFixed;
    int numFrames;
    int animationSpeed;
    int animationIndex;
    std::string currentAnimationName;
    std::map<std::string, Animation> animationMap;
    Transform* transform;
		SDL_Rect sourceRect;
		SDL_Rect destRect;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		SDL_Texture* texture;
	public:
		Sprite(std::string textureId) {
			SetTexture(AssetManager::GetTexture(textureId));
		}

    Sprite(std::string textureId, int numFrames, int animationSpeed, bool hasDirections, bool isFixed) {
      this->isAnimated = true;
      this->numFrames = numFrames;
      this->animationSpeed = animationSpeed;
      this->isFixed = isFixed;
      SetTexture(AssetManager::GetTexture(textureId));


      // Animations are much more complex than that...but for our little helicopter, this should do.
      if (hasDirections) {
        Animation downAnimation = Animation(0, numFrames, animationSpeed);
        Animation rightAnimation = Animation(1, numFrames, animationSpeed);
        Animation leftAnimation = Animation(2, numFrames, animationSpeed);
        Animation upAnimation = Animation(3, numFrames, animationSpeed);

        animationMap.emplace("DownAnimation", downAnimation);
        animationMap.emplace("RightAnimation", rightAnimation);
        animationMap.emplace("LeftAnimation", leftAnimation);
        animationMap.emplace("UpAnimation", upAnimation);
        this->animationIndex = 2;
        this->currentAnimationName = "DownAnimation";
      }
      else {
        Animation singleAnimation = Animation(0, numFrames, animationSpeed);
        animationMap.emplace("SingleAnimation", singleAnimation);
        this->animationIndex = 0;
        this->currentAnimationName = "SingleAnimation";
      }


    }

    void Play(std::string animationName) {
      animationIndex = animationMap[animationName].index;
      numFrames = animationMap[animationName].numFrames;
      animationSpeed = animationMap[animationName].animationSpeed;
      currentAnimationName = animationName;
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


      if (isAnimated) {
        // Cycle through numFrames and 0 everytime GetTicks is divisible by animationSpeed
        // This makes our animation really smooth!
        sourceRect.x = sourceRect.w * static_cast<int>(SDL_GetTicks() / animationSpeed % numFrames);
        sourceRect.y = sourceRect.h * animationIndex;
      }
      destRect.x = static_cast<int>(transform->position.x) - (isFixed ? 0 : Camera::source.x);
      destRect.y = static_cast<int>(transform->position.y) - (isFixed ? 0 : Camera::source.y);
      destRect.w = transform->width * transform->scale;
    	destRect.h = transform->height * transform->scale;
    }

    void Render(SDL_Renderer* renderer) override
    {
      Texture::Draw(texture, sourceRect, destRect, flip);
    }
};

#endif