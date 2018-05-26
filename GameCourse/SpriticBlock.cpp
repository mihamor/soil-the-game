#include "SpriticBlock.h"


interactionType SpriticBlock::interact() {
	return spriticType;
};

Sprite SpriticBlock::getSprite() {
	return sp;
}

SpriticBlock::SpriticBlock(char singnature, BlockType type, Texture *t) : AbstractBlock(t, singnature, type) {
	this->sp.setTexture(*t);
};
SpriticBlock::SpriticBlock(std::string fileName, char singnature, BlockType type) : AbstractBlock(fileName, singnature, type) {
	sp.setTexture(*(Texture*)rectangle.getTexture());
};
SpriticBlock::SpriticBlock(char signature, std::list<AbstractBlock *> & blocks) : AbstractBlock(signature, blocks) {
	sp.setTexture(*(Texture*)rectangle.getTexture());
};