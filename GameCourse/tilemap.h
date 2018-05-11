#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "PLAYER.hpp"
#include "Inventory.hpp"

//const int H = 18;
//const int W = 39;
const int H = 40;
const int W = 120;


namespace TMap {
	void saveTileMap(const char * FileName, sf::String TileMap[]);
	void loadTileMap(const char * FileName, sf::String TileMap[]);
	bool setBlock(Player * p, int x, int y, float offsetX, float offsetY, std::list<AbstractBlock*> blocks, sf::String * TileMap, sf::String * TileMapBg, Inventory& inv);
	void removeBlock(Player * p, int x, int y, float offsetX, float offsetY, std::list<AbstractBlock*> blocks, sf::String * TileMap, sf::String * TileMapBg, Inventory& inv);
	void copyFrom(String * from, String * to);
};
