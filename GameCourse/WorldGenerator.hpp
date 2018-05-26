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
	WorldGenerator();
	String * getBg();
	String * getMap();
	~WorldGenerator();
private:

	static bool randomBoolean(unsigned int percetnage);
	static String * generate();

	static bool hasBlockNeigh(int y, int x, String * map, char sign);
	static void fillGroundLevel(String * newMap);

	static void randMountains(String * newMap);
	static void fillGrass(String * newMap);
	static void fillRocks(String * newMap);
	static void fillTrees(String * newMap);

	static String * generateBg();
};

