#pragma once
#include "AbstractBlock.hpp"
class ChestBlock :
	public AbstractBlock
{
public:

	interactionType interact() {
		return chestType;
	}

	ChestBlock(Texture *t, char singnature, BlockType type);
	ChestBlock(std::string fileName, char singnature, BlockType type);
	ChestBlock(char signature, std::list<AbstractBlock *> & blocks);
};

