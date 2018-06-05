#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "PLAYER.hpp"
#include "Inventory.hpp"
#include "WorldDef.h"


namespace TMap {
	void saveTileMap(const char * FileName, sf::String TileMap[]);
	void loadTileMap(const char * FileName, sf::String TileMap[]);
	bool setBlock(Player * p, int x, int y, float offsetX, float offsetY, std::list<AbstractBlock*> blocks, sf::String * TileMap, sf::String * TileMapBg, Inventory& inv);
	bool removeBlock(Player * p, int x, int y, float offsetX, float offsetY, std::list<AbstractBlock*> blocks, sf::String * TileMap, sf::String * TileMapBg, Inventory& inv);
	void copyFrom(String * from, String * to);
	bool loadTileMapFromSlot(int slot, String* TileMap, String* TileMapBg);
	bool saveTileMapToSlot(int slot, String* TileMap, String* TileMapBg);
};
