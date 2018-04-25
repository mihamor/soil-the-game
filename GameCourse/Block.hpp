#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <assert.h>
#include <list>

const int BLOCK_SIZE = 32;
using namespace sf;

enum BlockType {
	Solid,
	Background
};

const char DEFAULT_BG_SINGNATURE = ' ';

class Block
{
public:
	RectangleShape rectangle;
	char singnature;
	BlockType type;

	Block(Texture *t, char singnature, BlockType type)
	{
		this->rectangle = RectangleShape(Vector2f(32, 32));
		this->singnature = singnature;
		this->rectangle.setTexture(t);
		this->type = type;
	}
	Block(String TileMap[], int i, int j)
	{
		rectangle = RectangleShape(Vector2f(32, 32));
		if(i < 18 && j < 40)
		singnature = TileMap[i][j];
		if(getCollisionBySignature())
			type = Solid;
		else type = Background;

	}
	bool getPermision()
	{
		switch(singnature)
		{
		case 'S': return true;
		case 'G': return true;
		case 'B': return false;
		case 'R': return true;
		case ' ': return false;
		case '-': return true;
			//....
		default: return false;
		}
	}
	bool getCollision()
	{	
			if (type == Background)
				return false;
			else if (type == Solid)
				return true;
			else assert(0);
	
	}
	bool getCollisionBySignature()
	{
		switch (singnature)
		{
		case 'S': return true;
		case 'G': return true;
		case 'B': return true;
		case 'R': return true;
		case ' ': return false;
		case '-': return false;
			//....
		default: return false;
		}
	}
	std::list<Block*> scanTile(String TileMap[], int H, int W)
	{
		std::list<Block*> res;

		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				Block *b = new Block(TileMap, i, j);
				if (!isContains(b, res))
					res.push_back(b);
			}
		}
		return res;
	}
	
	static Block *getBlock(std::list<Block*> vec, String TileMap[], int i, int j)
	{
		char sing = TileMap[i][j];
		for (std::list<Block*>::iterator i = vec.begin(); i != vec.end(); i++)
		{
			Block *b = *i;
			//std::cout << "GETBLOCK " << (char)b->singnature << std::endl;
			if (b->singnature == sing) return b;
		}
		return NULL;
		
	}
	static bool compare(Block *a, Block  *b)
	{
		if (a->singnature == b->singnature) return true;
		return false;
	}



	static void drawViewField(std::list<Block*> * blocks, String * TileMap, String * TileMapBg, double offsetX, double offsetY, int H, int W, RenderWindow & window)
	{
		RectangleShape rectangle;
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				Block *b = Block::getBlock(*blocks, TileMap, i, j);
				if(b->type == Background) b = Block::getBlock(*blocks, TileMapBg, i, j);
				if (b != NULL)
					rectangle = b->rectangle;
				else 
				{
					fprintf(stderr, "Unknown block was found ");
					std::cout << (char)TileMap[i][j] << std::endl;
					abort();
				}
				rectangle.setPosition(j * 32 - offsetX, i * 32 - offsetY);
				window.draw(rectangle);
			}
	}
	
private:
	bool isContains(Block *b, std::list<Block*> vec)
	{
		for (std::list<Block*>::iterator i = vec.begin(); i != vec.end(); i++)
		{
			Block *a = *i;
			if (compare(a, b)) return true;
		}
		return false;
	}
	
};

