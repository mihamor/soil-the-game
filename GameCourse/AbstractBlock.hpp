#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <assert.h>
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
	spriticType
};


class AbstractBlock
{
protected:

	std::string fileName;

public:
	RectangleShape rectangle;
	char singnature;
	BlockType type;

	AbstractBlock(Texture *t, char singnature, BlockType type)
	{
		this->fileName = "<none>";
		this->rectangle = RectangleShape(Vector2f(32, 32));
		this->singnature = singnature;
		this->rectangle.setTexture(t);
		this->type = type;
	}
	AbstractBlock(std::string fileName, char singnature, BlockType type)
	{
		this->fileName = fileName;
		Texture *  t = new Texture();
		t->loadFromFile(fileName);
		this->rectangle = RectangleShape(Vector2f(32, 32));
		this->singnature = singnature;
		this->rectangle.setTexture(t);
		this->type = type;
	}

	AbstractBlock(char signature, std::list<AbstractBlock *> & blocks) // @REDO FOR MECH BLOCKS
	{
		this->singnature = signature;
		for (AbstractBlock * b : blocks) {
			if (b->singnature == signature) {
				this->fileName = b->fileName;
				this->rectangle = RectangleShape(Vector2f(32, 32));
				this->rectangle.setTexture(b->rectangle.getTexture());
				this->type = b->type;
			}
		}

	}
	static bool hasBlockNeigh(int y, int x, String * map, char sign) {
		for (int y1 = y - 1; y1 < y + 2; y1++) {
			for (int x1 = x - 1; x1 < x + 2; x1++) {
				if ((y1 == y - 1 && x1 == x - 1)
					|| (y1 == y - 1 && x1 == x + 1)
					|| (y1 == y + 1 && x1 == x - 1)
					|| (y1 == y + 1 && x1 == x + 1)) continue;
				if (y1 < H && x1 < W && map[y1][x1] == sign) return true;
			}
		}

		return false;
	}
	static AbstractBlock * getBlockFromList(char signature, std::list<AbstractBlock *> & blocks) {
		for (AbstractBlock * b : blocks) {
			if (b->singnature == signature) {
				return b;
			}
		}
		return nullptr;
	}

	std::string getFileName() {
		return this->fileName;
	}
	bool getPermision()
	{
		switch (singnature)
		{
		case 'S': return true;
		case 'G': return true;
		case 'B': return false;
		case 'R': return true;
		case ' ': return false;
		case '-': return true;
			//....
		default: return true;
		}
	}
	bool getCollision()
	{
		if (type == Background)
			return false;
		else if (type == Solid)
			return true;
		else assert(0);
		return false;
	}
	virtual interactionType interact() = 0;

	static bool getCollisionByChar(char s, std::list<AbstractBlock *> & blocks) {

		for (AbstractBlock * b : blocks) {
			if (b->singnature == s) {
				return b->getCollision();
			}
		}
		throw new std::exception("No such signature where found");
		return false;
	}

	static AbstractBlock *getBlock(std::list<AbstractBlock*> vec, String TileMap[], int i, int j)
	{
		char sing = TileMap[i][j];
		for (std::list<AbstractBlock*>::iterator i = vec.begin(); i != vec.end(); i++)
		{
			AbstractBlock *b = *i;
			//std::cout << "GETBLOCK " << (char)b->singnature << std::endl;
			if (b->singnature == sing) return b;
		}
		return NULL;

	}
	static bool compare(AbstractBlock *a, AbstractBlock  *b)
	{
		if (a->singnature == b->singnature) return true;
		return false;
	}


	static bool isContains(AbstractBlock *b, std::list<AbstractBlock*> vec)
	{
		for (std::list<AbstractBlock*>::iterator i = vec.begin(); i != vec.end(); i++)
		{
			AbstractBlock *a = *i;
			if (compare(a, b)) return true;
		}
		return false;
	}
private:


};

