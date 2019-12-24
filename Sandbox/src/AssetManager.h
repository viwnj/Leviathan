#pragma once
#include <map>
#include <string>
#include <SDL.h>
#include "Texture.h"
class AssetManager
{
	public:
		std::map<std::string, SDL_Texture*> textureMap;
		void ClearData();
		void AddTexture(std::string textureId, const char* filePath, SDL_Renderer* renderer);
		SDL_Texture* GetTexture(std::string textureId);
};

