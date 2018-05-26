#include "Block.hpp"

interactionType Block::interact() {
	return removeType;
};

Block::Block(Texture *t, char singnature, BlockType type) : AbstractBlock(t, singnature, type) {};
Block::Block(std::string fileName, char singnature, BlockType type) : AbstractBlock(fileName, singnature, type) {};
Block::Block(char signature, std::list<AbstractBlock *> & blocks) : AbstractBlock(signature, blocks) {};