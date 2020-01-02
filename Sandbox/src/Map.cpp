#include <fstream>
#include <iostream>
#include "Map.h"

Map::Map(Layer* layer, SDL_Texture* texture, int scale, int tileSize) {
	this->texture = texture;
	this->scale = scale;
	this->tileSize = tileSize;
	this->layer = layer;
}

void Map::LoadMap(std::string filePath, int mapSizeX, int mapSizeY) {
	std::fstream mapFile;
	mapFile.open(filePath);

	for (int y = 0; y < mapSizeY; y++) {
		for (int x = 0; x < mapSizeX; x++) {
			char ch;
			mapFile.get(ch);
			int sourceRectY = atoi(&ch) * tileSize;
			mapFile.get(ch);
			int sourceRectX = atoi(&ch) * tileSize;

			AddTile(texture,sourceRectX, sourceRectY, x * (scale * tileSize), y * (scale * tileSize));
			mapFile.ignore();
		}
	}

	mapFile.close();

}

void Map::AddTile(SDL_Texture* tex, int sourceX, int sourceY, int x, int y) {
	Entity* tile = new Entity("tile");
	tile->AddComponent<Tile>(tex, sourceX, sourceY, x, y, tileSize, scale);
	this->layer->AddEntity(tile);
}