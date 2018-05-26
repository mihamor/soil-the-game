#pragma once
#include "AbstractBlock.hpp"
#include "anim.hpp"

using namespace sf;
class SpriticBlock :public AbstractBlock
{
	Sprite sp;
public:
	interactionType interact() {
		return spriticType;
	};

	Sprite getSprite() {
		return sp;
	}

	SpriticBlock(char singnature, BlockType type, Texture *t) : AbstractBlock(t, singnature, type) {
		this->sp.setTexture(*t);
	};
	SpriticBlock(std::string fileName, char singnature, BlockType type) : AbstractBlock(fileName, singnature, type) { 
		sp.setTexture(*(Texture*)rectangle.getTexture());
	};
	SpriticBlock(char signature, std::list<AbstractBlock *> & blocks) : AbstractBlock(signature, blocks) {
		sp.setTexture(*(Texture*)rectangle.getTexture());
	};
};

