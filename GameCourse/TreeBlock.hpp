#pragma once
#include "AbstractBlock.hpp"
#include "tilemap.h"

const int maxTreeHeight = 5;
const int maxTreeRadius = 3;
const char DEFAULT_TREE_SIGN = 't';
const char DEFAULT_LEAVES_SIGN = 'l';

class TreeBlock : public AbstractBlock
{

public:
	interactionType interact() {
		return treeType;
	};

	TreeBlock(Texture *t, char singnature, BlockType type) : AbstractBlock(t, singnature, type) {};
	TreeBlock(std::string fileName, char singnature, BlockType type) : AbstractBlock(fileName, singnature, type) {};
	TreeBlock(char signature, std::list<AbstractBlock *> & blocks) : AbstractBlock(signature, blocks) {};


	bool static placeTree(int y, int x, String * TileMap) {

		int height = (rand() % (maxTreeHeight)  + 5);
		int radius = rand() % maxTreeRadius + 1;

		int i = y;
		for (; i > y - height; i--) {
			if (i < H && x < W && i > 0 && x > 0
				&& TileMap[i][x] == DEFAULT_BG_SINGNATURE) TileMap[i][x] = DEFAULT_TREE_SIGN;
			else break;
		}
		for (int j = i - radius; j <= i + radius; j++) {
			for (int k = x - radius; k <= x + radius; k++) {
				if ((j == i - radius && k == x - radius)
					|| (j == i - radius && k == x + radius)
					|| (j == i + radius && k == x - radius)
					|| (j == i + radius && k == x + radius)) continue;
				if (j < H && k < W && j > 0 && k > 0
					&& TileMap[j][k] == DEFAULT_BG_SINGNATURE) TileMap[j][k] = DEFAULT_LEAVES_SIGN;
			}
		}
		return true;
	}
};

