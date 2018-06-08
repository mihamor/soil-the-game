#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "tinyxml.h"
#include "WorldDef.h"

const char DEFAULT_BG_SINGNATURE = ' ';
const int BLOCK_SIZE = 32;
using namespace sf;

enum BlockType {
	Solid,
	Background
};

enum interactionType {
	removeType,
	doorType,
	treeType,
	craftType,
	itemType,
	spriticType,
	weaponItemType,
	chestType
};


class AbstractBlock
{
protected:

	std::string fileName;

public:
	RectangleShape rectangle;
	char singnature;
	BlockType type;

	AbstractBlock(Texture *t, char singnature, BlockType type);
	AbstractBlock(std::string fileName, char singnature, BlockType type);

	AbstractBlock(char signature, std::list<AbstractBlock *> & blocks); // @REDO FOR MECH BLOCKS
	static bool hasBlockNeigh(int y, int x, String * map, char sign);
	static AbstractBlock * getBlockFromList(char signature, std::list<AbstractBlock *> & blocks);
	std::string getFileName();
	bool getPermision();
	bool getCollision();
	virtual interactionType interact() = 0;
	static bool getCollisionByChar(char s, std::list<AbstractBlock *> & blocks);
	static AbstractBlock *getBlock(std::list<AbstractBlock*> vec, String TileMap[], int i, int j);
	static bool compare(AbstractBlock *a, AbstractBlock  *b);
	static bool isContains(AbstractBlock *b, std::list<AbstractBlock*> vec);
};

