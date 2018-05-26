#pragma once
#include "AbstractBlock.hpp"


const char DEFAULT_BENCH_SIGN = 'K';
const char DEFAULT_FURNACE_SIGN = 'F';
class WorkbenchBlock : public AbstractBlock
{
private:
	std::string id;
public:
	interactionType interact();

	std::string getId();

	WorkbenchBlock(Texture *t, char singnature, BlockType type, std::string id);
	WorkbenchBlock(std::string fileName, char singnature, BlockType type, std::string id);
	WorkbenchBlock(char signature, std::list<AbstractBlock *> & blocks, std::string id);
};

