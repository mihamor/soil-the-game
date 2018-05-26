#pragma once
#include "AbstractBlock.hpp"

const char doorOpenSign = 'd';
const char doorClosedSign = 'D';


class DoorBlock : public AbstractBlock
{
public:
	interactionType interact();
	DoorBlock(Texture *t, char singnature, BlockType type);
	DoorBlock(std::string fileName, char singnature, BlockType type);
	DoorBlock(char signature, std::list<AbstractBlock *> & blocks);

	BlockType doorUse(int posx, int posy, String TileMap[]);

	static std::vector<int> getDoorNeighboors(int posx, int posy, String TileMap[]);

	static bool isDoorBlock(char sign);

};

