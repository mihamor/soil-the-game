#include "WorkbenchBlock.hpp"

interactionType WorkbenchBlock::interact() {
	return craftType;
};

std::string  WorkbenchBlock::getId() {
	return this->id;
}

WorkbenchBlock::WorkbenchBlock(Texture *t, char singnature, BlockType type, std::string id) : AbstractBlock(t, singnature, type) { this->id = id; };
WorkbenchBlock::WorkbenchBlock(std::string fileName, char singnature, BlockType type, std::string id) : AbstractBlock(fileName, singnature, type) { this->id = id; };
WorkbenchBlock::WorkbenchBlock(char signature, std::list<AbstractBlock *> & blocks, std::string id) : AbstractBlock(signature, blocks) { this->id = id; };