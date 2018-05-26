#include "Item.hpp"


interactionType Item::interact() {
	return itemType;
};

Item::Item(Texture *t, char singnature, BlockType type) : AbstractBlock(t, singnature, type) {};
Item::Item(std::string fileName, char singnature, BlockType type) : AbstractBlock(fileName, singnature, type) {};
Item::Item(char signature, std::list<AbstractBlock *> & blocks) : AbstractBlock(signature, blocks) {};