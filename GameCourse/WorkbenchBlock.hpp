#pragma once
#include "AbstractBlock.hpp"


const char DEFAULT_BENCH_SIGN = 'K';
const char DEFAULT_FURNACE_SIGN = 'F';
class WorkbenchBlock : public AbstractBlock
{
private:
	std::string id;
public:
	interactionType interact() {
		return craftType;
	};

	std::string getId() {
		return this->id;
	}

	WorkbenchBlock(Texture *t, char singnature, BlockType type, std::string id) : AbstractBlock(t, singnature, type) { this->id = id; };
	WorkbenchBlock(std::string fileName, char singnature, BlockType type, std::string id) : AbstractBlock(fileName, singnature, type) { this->id = id; };
	WorkbenchBlock(char signature, std::list<AbstractBlock *> & blocks, std::string id) : AbstractBlock(signature, blocks) { this->id = id; };
};

