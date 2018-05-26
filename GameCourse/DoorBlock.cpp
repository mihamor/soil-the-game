#include "DoorBlock.h"
interactionType DoorBlock::interact() {
	return doorType;
};

DoorBlock::DoorBlock(Texture *t, char singnature, BlockType type) : AbstractBlock(t, singnature, type) {};
DoorBlock::DoorBlock(std::string fileName, char singnature, BlockType type) : AbstractBlock(fileName, singnature, type) {};
DoorBlock::DoorBlock(char signature, std::list<AbstractBlock *> & blocks) : AbstractBlock(signature, blocks) {};

BlockType DoorBlock::doorUse(int posx, int posy, String TileMap[]) {
	if (this->type == Solid) {
		TileMap[posy][posx] = doorOpenSign;
		auto n = getDoorNeighboors(posx, posy, TileMap);
		for (int i : n) TileMap[i][posx] = doorOpenSign;
	}
	else {
		TileMap[posy][posx] = doorClosedSign;
		auto n = getDoorNeighboors(posx, posy, TileMap);
		for (int i : n) TileMap[i][posx] = doorClosedSign;
	}
	return type;
}

std::vector<int> DoorBlock::getDoorNeighboors(int posx, int posy, String TileMap[]) {
	std::vector<int> neighboors;

	if (posy > 0 && DoorBlock::isDoorBlock(TileMap[posy - 1][posx])) neighboors.push_back(posy - 1);
	else if (DoorBlock::isDoorBlock(TileMap[posy + 1][posx])) neighboors.push_back(posy + 1);
	return neighboors;
}

bool DoorBlock::isDoorBlock(char sign) {
	return sign == doorClosedSign ? true : sign == doorOpenSign ? true : false;
}