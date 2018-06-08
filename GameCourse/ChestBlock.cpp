#include "ChestBlock.hpp"

ChestBlock::ChestBlock(Texture *t, char singnature, BlockType type) : AbstractBlock(t, singnature, type) {};
ChestBlock::ChestBlock(std::string fileName, char singnature, BlockType type) : AbstractBlock(fileName, singnature, type) {};
ChestBlock::ChestBlock(char signature, std::list<AbstractBlock *> & blocks) : AbstractBlock(signature, blocks) {};