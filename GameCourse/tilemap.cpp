#include "tilemap.h"

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

void TMap::setBlock(Player * p, int x, int y, float offsetX, float offsetY, std::list<AbstractBlock*> blocks, sf::String * TileMap, sf::String * TileMapBg, Inventory& inv) {
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
				else return;
			}
			p->reduceAmount(inv.getList());
		}
	}
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
			else TileMap[posy][posx] = DEFAULT_BG_SINGNATURE;
			//if(check->type == Solid) TileMap[posy][posx] = DEFAULT_BG_SINGNATURE;
			//else TileMapBg[posy][posx] = DEFAULT_BG_SINGNATURE;
			inv.addSlot(check);
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
