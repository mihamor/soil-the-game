#pragma once
#include "AbstractBlock.hpp"

using namespace sf;
class SpriticBlock :public AbstractBlock
{
	Sprite sp;
public:
	interactionType interact();
	Sprite getSprite();
	SpriticBlock(char singnature, BlockType type, Texture *t);
	SpriticBlock(std::string fileName, char singnature, BlockType type);
	SpriticBlock(char signature, std::list<AbstractBlock *> & blocks);
};

