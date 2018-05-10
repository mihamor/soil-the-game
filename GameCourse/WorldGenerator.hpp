#pragma once
#include "tilemap.h"
#include "DoorBlock.h"
#include "Block.hpp"
#include "TreeBlock.hpp"
#include <time.h>

using namespace sf;

const int groundLevel = H / 2;
const int jumpDist = 3;

class WorldGenerator
{
	String * bg;
	String * map;

public:
	WorldGenerator() {
		bg = generateBg();
		map = generate();
	}
	String * getBg() {
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
		fillGroundLevel(newMap);
		randMountains(newMap);
		fillGrass(newMap);
		fillRocks(newMap);
		fillTrees(newMap);


		return newMap;
	};

	static bool hasBlockNeigh(int y, int x, String * map, char sign) {
		for (int y1 = y - 1; y1 < y + 2; y1++) {
			for (int x1 = x - 1; x1 < x + 2; x1++) {
				if ((y1 == y - 1 && x1 == x - 1)
					//|| (y1 == y - 1 && x1 == x + 1)
					//|| (y1 == y + 1 && x1 == x - 1)
					|| (y1 == y + 1 && x1 == x + 1)) continue;
				if (y1 < H && x1 < W && map[y1][x1] == sign) return true;
			}
		}

		return false;
	}
	static void fillGroundLevel(String * newMap) {
		for (int y = 0; y < H; y++) {
			for (int x = 0; x < W + 1; x++) {
				//std::string block = DEFAULT_BG_SINGNATURE + "";
				if (x == 0 || x == W - 1) newMap[y].insert(x, "B");
				else if (y > H - groundLevel && y != H - 1) newMap[y].insert(x, "S");
				else if (y == H - 1) newMap[y].insert(x, "B");
				else newMap[y].insert(x, " ");
			}
		}
	}

	static void randMountains(String * newMap) {
		srand(time(0));
		int h = jumpDist;
		int lastRes = jumpDist;
		for (int x = 1; x < W - 1; x++) {
			h = (rand() % jumpDist + 1);
			if ((int)abs(lastRes - h) > jumpDist) h = abs(h - lastRes);
			lastRes = h;
			for (int y = 0; y < h; y++) newMap[groundLevel - y][x] = 'S';
		}
	}
	static void fillGrass(String * newMap) {
		for (int y = 1; y < H - 1; y++) {
			for (int x = 1; x < W - 1; x++) {
				if (newMap[y][x] == ' ' && hasBlockNeigh(y, x, newMap, 'S')) newMap[y][x] = 'G';
			}
		}
	}
	static void fillRocks(String * newMap) {
		for (int x = 1; x < W - 1; x++) {
			int h = (rand() % groundLevel / 4 + groundLevel / 2);
			for (int y = 0; y < h; y++) newMap[H - 2 - y][x] = 'R';
		}
	}
	static void fillTrees(String * newMap) {
		int treesCount = W / 10;
		int j = 0;
		int i = 0;
		while (j < treesCount && i < 100000) {
			for (int y = groundLevel - jumpDist; y < groundLevel + jumpDist; y++) {
				int x = (rand() % (W - 1)) + 1;
				if (newMap[y][x] == ' ' && hasBlockNeigh(y, x, newMap, 'G')) {
					TreeBlock::placeTree(y, x, newMap);
					j++;
				}
			}
			i++;
		}
	}

	static String * generateBg() {
		String * newMap = new String[H];
		for (int y = 0; y < H; y++) {
			for (int x = 0; x < W + 1; x++) {
				 if (y > H - groundLevel && y != H - 1) newMap[y].insert(x, "s");
				else newMap[y].insert(x, " ");
			}
		}

		return newMap;
	};
};

