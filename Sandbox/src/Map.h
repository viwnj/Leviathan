#pragma once
#include <string>
#include <SDL.h>
#include "Layer.h"
#include "Entity.h"
#include "Components/Tile.h"

class Map {
	private:
		SDL_Texture* texture;
		Layer* layer;
		int scale;
		int tileSize;
	public:
		Map(Layer* layer ,SDL_Texture* texture, int scale, int tileSize);
		~Map();

		void LoadMap(std::string filePath, int mapSizeX, int mapSizeY);
		void AddTile(SDL_Texture* tex, int sourceX, int sourceY, int x, int y);
};