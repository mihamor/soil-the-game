#include "tilemap.h"
#include "DoorBlock.h"
#include <iostream>
#include <string>
#include <fstream>
#include <assert.h>


static void copyTileMapToCharMatrix(char map[H][W + 1], String * TileMap);
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

	copyTileMapToCharMatrix(map, TileMap);

	FILE *fp;
	fopen_s(&fp, FileName, "w");
	if (!fp) std::cerr << "Can't open file " << FileName << std::endl;
	for (int i = 0; i < H; i++)
	{
		fputs(map[i], fp);
		if (i != H - 1)
			fputs("\n", fp);
	}
	fclose(fp);
}
static void copyTileMapToCharMatrix(char map[H][W+1], String * TileMap){
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			map[i][j] = TileMap[i][j];
		}
		map[i][W] = '\0';
	}
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
		if(p->getHand()->block->interact() == itemType
		|| p->getHand()->block->interact() == weaponItemType) return false;
		int posx = (x + (int)offsetX) / 32;
		int posy = (y + (int)offsetY) / 32;
		AbstractBlock *check = AbstractBlock::getBlock(blocks, TileMap, posy, posx);
		if (check->getSingature() == DEFAULT_BG_SINGNATURE)
		{ // проверка если блок, на место которого нужно поставить - бэкграундный блок
			Slot * h = p->getHand();
			if(h->block->getBlockType() == Solid) TileMap[posy][posx] = h->block->getSingature();
			else if(h->block->getBlockType() == Background){
				check = AbstractBlock::getBlock(blocks, TileMapBg, posy, posx);
				if (check->getSingature() == DEFAULT_BG_SINGNATURE) TileMapBg[posy][posx] = h->block->getSingature();
				else return false;
			}
			//AbstractBlock * bHand = p->getHand()->block;
			//p->reduceAmount(inv.getList());
			inv.reduceAmount(p);
			return true;
		}
		return false;
	}
	return false;
}

bool TMap::removeBlock(Player * p, int x, int y, float offsetX, float offsetY, std::list<AbstractBlock*> blocks, sf::String * TileMap, sf::String * TileMapBg, Inventory& inv) {
	if (p->isInRange(x, y, offsetX, offsetY))
	{
		int posx = (x + (int)offsetX) / 32;
		int posy = (y + (int)offsetY) / 32;
		bool isBg = false;
		AbstractBlock *check = AbstractBlock::getBlock(blocks, TileMap, posy, posx);
		if (check->getSingature() == DEFAULT_BG_SINGNATURE)
		{
			check = AbstractBlock::getBlock(blocks, TileMapBg, posy, posx);
			isBg = true;
		}
		if (check->getPermision())
		{
			
			if(isBg) TileMapBg[posy][posx] = DEFAULT_BG_SINGNATURE;
			else {
				TileMap[posy][posx] = DEFAULT_BG_SINGNATURE;
			}
			//if(check->type == Solid) TileMap[posy][posx] = DEFAULT_BG_SINGNATURE;
			//else TileMapBg[posy][posx] = DEFAULT_BG_SINGNATURE;
			if (check->interact() == doorType) inv.addSlot(AbstractBlock::getBlockFromList(doorClosedSign, blocks));
			else inv.addSlot(check);
			return true;
		}
		else return false;
	}
	else return false;
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
