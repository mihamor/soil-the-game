#pragma once

#include "AbstractBlock.hpp"

class Block : public AbstractBlock
{	
public:
	interactionType interact() {
		return removeType;
	};

	Block(Texture *t, char singnature, BlockType type) : AbstractBlock(t, singnature, type) {};
	Block(std::string fileName, char singnature, BlockType type) : AbstractBlock(fileName, singnature, type) {};
	Block(char signature, std::list<AbstractBlock *> & blocks) : AbstractBlock(signature, blocks) {};
};

