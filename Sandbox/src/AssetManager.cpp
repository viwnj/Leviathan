#include "AssetManager.h"
#include "Renderer.h"

std::map<std::string, SDL_Texture*> AssetManager::textureMap;
std::map<std::string, TTF_Font*> AssetManager::fontMap;
void AssetManager::ClearData() {
	textureMap.clear();
	fontMap.clear();
}

void AssetManager::AddTexture(std::string textureId, const char* filePath) {
	textureMap.emplace(textureId, Texture::LoadTexture(filePath));
}

SDL_Texture* AssetManager::GetTexture(std::string textureId) {
	int w, h;
	SDL_Texture* texture = textureMap[textureId];

	std::cout << "isTexture:" << SDL_QueryTexture(texture, NULL, NULL, &w, &h) << std::endl;

	return texture;
}

void AssetManager::AddFont(std::string fontId, const char* filePath, int fontSize) {
	fontMap.emplace(fontId, Font::LoadFont(filePath, fontSize));
}

TTF_Font* AssetManager::GetFont(std::string fontId) {
	return fontMap[fontId];
}
