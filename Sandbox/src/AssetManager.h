#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include <map>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Texture.h"
#include "Font.h"
class AssetManager
{
	public:
		static std::map<std::string, SDL_Texture*> textureMap;
		static std::map<std::string, TTF_Font*> fontMap;
		static void ClearData();
		static void AddTexture(std::string textureId, const char* filePath);
		static SDL_Texture* GetTexture(std::string textureId);
		static void AddFont(std::string fontId, const char * filePath, int fontSize);
		static TTF_Font* GetFont(std::string fontId);
};

#endif