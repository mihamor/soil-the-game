#pragma once

#include "AbstractBlock.hpp"

class Block : public AbstractBlock
{	
public:
	interactionType interact();
	Block(Texture *t, char singnature, BlockType type);
	Block(std::string fileName, char singnature, BlockType type);
	Block(char signature, std::list<AbstractBlock *> & blocks);
};

