#pragma once
#include "AbstractBlock.hpp"

const int maxTreeHeight = 5;
const int maxTreeRadius = 3;
const char DEFAULT_TREE_SIGN = 't';
const char DEFAULT_LEAVES_SIGN = 'l';

class TreeBlock : public AbstractBlock
{

public:
	interactionType interact();
	TreeBlock(Texture *t, char singnature, BlockType type);
	TreeBlock(std::string fileName, char singnature, BlockType type);
	TreeBlock(char signature, std::list<AbstractBlock *> & blocks);


	bool static placeTree(int y, int x, String * TileMap);
};

