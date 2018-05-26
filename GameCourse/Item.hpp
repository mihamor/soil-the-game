#pragma once
#include "AbstractBlock.hpp"
class Item : public AbstractBlock
{
public:
	interactionType interact();
	Item(Texture *t, char singnature, BlockType type);
	Item(std::string fileName, char singnature, BlockType type);
	Item(char signature, std::list<AbstractBlock *> & blocks);
};

