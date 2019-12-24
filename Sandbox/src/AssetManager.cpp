#include "AssetManager.h"


void AssetManager::ClearData() {
	textureMap.clear();
}

void AssetManager::AddTexture(std::string textureId, const char* filePath, SDL_Renderer* renderer) {
	textureMap.emplace(textureId, Texture::LoadTexture(filePath, renderer));
}

SDL_Texture* AssetManager::GetTexture(std::string textureId) {
	int w, h;
	SDL_Texture* texture = textureMap[textureId];

	std::cout << "isTexture:" << SDL_QueryTexture(texture, NULL, NULL, &w, &h) << std::endl;

	return texture;
}
