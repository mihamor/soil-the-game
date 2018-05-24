#include "tilemap.h"
#include "DoorBlock.h"
#include <iostream>
#include <string>
#include <fstream>
#include <assert.h>


bool TMap::isEmptySlot(unsigned int slot) {
	
	std::string FileName;
	switch (slot)
	{
	case 1:
		FileName = "saves/map1.mf";
		break;
	case 2:
		FileName = "saves/map2.mf";
		break;
	case 3:
		FileName = "saves/map3.mf";
		break;
	default:
		assert(0 && "Unknown slot");
		break;
	}

	std::ifstream is;
	is.open(FileName.c_str(), std::ios::binary);
	if (!is.is_open()) return true;
	is.seekg(0, std::ios::end);
	int length = is.tellg();
	std::cout << length << std::endl;
	is.close();
	return length <= 0;
}
bool TMap::loadTileMapFromSlot(int slot, String* TileMap, String* TileMapBg) {
	switch (slot)
	{
	case 1:
		TMap::loadTileMap("saves/map1.mf", TileMap);
		TMap::loadTileMap("saves/mapbg1.mf", TileMapBg);
		break;
	case 2:
		TMap::loadTileMap("saves/map2.mf", TileMap);
		TMap::loadTileMap("saves/mapbg2.mf", TileMapBg);
		break;
	case 3:
		TMap::loadTileMap("saves/map3.mf", TileMap);
		TMap::loadTileMap("saves/mapbg3.mf", TileMapBg);
		break;
	default:
		return false;
		break;
	}
	return true;
}

bool TMap::saveTileMapToSlot(int slot, String* TileMap, String* TileMapBg) {
	switch (slot)
	{
	case 1:
		TMap::saveTileMap("saves/map1.mf", TileMap);
		TMap::saveTileMap("saves/mapbg1.mf", TileMapBg);
		break;
	case 2:
		TMap::saveTileMap("saves/map2.mf", TileMap);
		TMap::saveTileMap("saves/mapbg2.mf", TileMapBg);
		break;
	case 3:
		TMap::saveTileMap("saves/map3.mf", TileMap);
		TMap::saveTileMap("saves/mapbg3.mf", TileMapBg);
		break;
	default:
		return false;
		break;
	}
	return true;
}

void TMap::saveTileMap(const char * FileName, String TileMap[])
{
	char map[H][W + 1];

	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W + 1; j++)
		{
			map[i][j] = TileMap[i][j];
		}
		map[i][W] = '\0';
	}

	FILE *fp;
	fopen_s(&fp, FileName, "w");
	for (int i = 0; i < H; i++)
	{
		fputs(map[i], fp);
		if (i != H - 1)
			fputs("\n", fp);
	}
	fclose(fp);
}
void TMap::loadTileMap(const char * FileName, String TileMap[])
{
	char map[H][W + 1];

	FILE *fp;
	fopen_s(&fp, FileName, "r");
	for (int i = 0; i < H; i++)
	{
		fgets(map[i], W + 2, fp);
		map[i][W] = '\0';
	}
	fclose(fp);

	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W ; j++)
		{
			TileMap[i][j] = map[i][j];
		}
		TileMap[i][W] = '\0';
	}
	
}

bool TMap::setBlock(Player * p, int x, int y, float offsetX, float offsetY, std::list<AbstractBlock*> blocks, sf::String * TileMap, sf::String * TileMapBg, Inventory& inv) {
	if (p->isInRange(x, y, offsetX, offsetY) && p->getHand() != NULL) // поставить блок
	{
		int posx = (x + (int)offsetX) / 32;
		int posy = (y + (int)offsetY) / 32;
		AbstractBlock *check = AbstractBlock::getBlock(blocks, TileMap, posy, posx);
		if (check->singnature == DEFAULT_BG_SINGNATURE)
		{ // проверка если блок, на место которого нужно поставить - бэкграундный блокв
			Slot * h = p->getHand();
			if(h->block->type == Solid) TileMap[posy][posx] = h->block->singnature;
			else if(h->block->type == Background){
				check = AbstractBlock::getBlock(blocks, TileMapBg, posy, posx);
				if (check->singnature == DEFAULT_BG_SINGNATURE) TileMapBg[posy][posx] = h->block->singnature;
				else return false;
			}
			p->reduceAmount(inv.getList());
			return true;
		}
		return false;
	}
	return false;
}

void TMap::removeBlock(Player * p, int x, int y, float offsetX, float offsetY, std::list<AbstractBlock*> blocks, sf::String * TileMap, sf::String * TileMapBg, Inventory& inv) {
	if (p->isInRange(x, y, offsetX, offsetY))
	{
		int posx = (x + (int)offsetX) / 32;
		int posy = (y + (int)offsetY) / 32;
		bool isBg = false;
		AbstractBlock *check = AbstractBlock::getBlock(blocks, TileMap, posy, posx);
		if (check->singnature == DEFAULT_BG_SINGNATURE)
		{
			check = AbstractBlock::getBlock(blocks, TileMapBg, posy, posx);
			isBg = true;
		}
		if (check->getPermision())
		{
			if (isBg) TileMapBg[posy][posx] = DEFAULT_BG_SINGNATURE;
			else {
				TileMap[posy][posx] = DEFAULT_BG_SINGNATURE;
			}
			//if(check->type == Solid) TileMap[posy][posx] = DEFAULT_BG_SINGNATURE;
			//else TileMapBg[posy][posx] = DEFAULT_BG_SINGNATURE;
			if (check->interact() == doorType) inv.addSlot(AbstractBlock::getBlockFromList(doorClosedSign, blocks));
			else inv.addSlot(check);
		}
	}
}

void TMap::copyFrom(String * from, String * to) {
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			to[i][j] = from[i][j];
			to[H - 1][W] = '/0';
		}
		to[i][W] = '/0';
	}
}
