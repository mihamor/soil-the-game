#pragma once
#include "AbstractBlock.hpp"
class DoorBlock : public AbstractBlock
{
public:
	interactionType interact() {
		return doorType;
	};

	DoorBlock(Texture *t, char singnature, BlockType type) : AbstractBlock(t, singnature, type) {};
	DoorBlock(std::string fileName, char singnature, BlockType type) : AbstractBlock(fileName, singnature, type) {};
	DoorBlock(char signature, std::list<AbstractBlock *> & blocks) : AbstractBlock(signature, blocks) {};

	BlockType doorUse() {
		if (this->type == Solid) {
			this->rectangle.setFillColor(Color(105, 105, 105));
			this->type = Background;
		}
		else {
			this->type = Solid;
			this->rectangle.setFillColor(Color::White);
		}
		return type;
	}

};

