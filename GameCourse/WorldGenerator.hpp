#pragma once
#include "tilemap.h"
#include "DoorBlock.h"
#include "Block.hpp"

using namespace sf;
class WorldGenerator
{
	String * bg;
	String * map;

public:
	WorldGenerator() {
		bg = generateBg();
		map = generate();
	}
	String * getBg(){
		return this->bg;
	}
	String * getMap() {
		return this->map;
	}
	~WorldGenerator() {
	}
private:
	static String * generate() {
		String * newMap = new String[H];
		for (int y = 0; y < H; y++) {
			for (int x = 0; x < W + 1; x++) {
				//std::string block = DEFAULT_BG_SINGNATURE + "";
				if (x == 0 || x == W-1) newMap[y].insert(x, "B");
				else if (y > H - 5 && y != H-1) newMap[y].insert(x, "G");
				else if(y == H-1 ) newMap[y].insert(x, "B");
				else newMap[y].insert(x, " ");
			}
		}

		return newMap;
	};
	static String * generateBg() {
		String * newMap = new String[H];
		for (int y = 0; y < H; y++) {
			for (int x = 0; x < W + 1; x++) {
				 if (y > H - 5 && y != H - 1) newMap[y].insert(x, "s");
				else newMap[y].insert(x, " ");
			}
		}

		return newMap;
	};
};

