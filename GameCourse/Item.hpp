#pragma once
#include "AbstractBlock.hpp"
class Item : public AbstractBlock
{
public:
	interactionType interact() {
		return itemType;
	};

	Item(Texture *t, char singnature, BlockType type) : AbstractBlock(t, singnature, type) {};
	Item(std::string fileName, char singnature, BlockType type) : AbstractBlock(fileName, singnature, type) {};
	Item(char signature, std::list<AbstractBlock *> & blocks) : AbstractBlock(signature, blocks) {};
};

