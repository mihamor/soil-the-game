#pragma once
#include "tilemap.h"
#include "DoorBlock.h"
#include "Block.hpp"
#include "TreeBlock.hpp"
#include <time.h>

using namespace sf;

const int groundLevel = H / 2;
const int jumpDist = 15;



//builder
class AbstractWorldGenerator{
	String * bg;
	String * map;
public:
	
	virtual void generateForeground() = 0;
	virtual void generateBackground() = 0;
	virtual void generateMountains() = 0;
	virtual void fillGroundLevel() = 0;
	virtual void fillGrass() = 0;
	virtual void fillRocks() = 0;
	virtual void fillTrees() = 0;
	virtual String * dispatchForeground() = 0;
	virtual String * dispatchBackground() = 0;
	

private:

	
};


struct Map {
public:
	String * background;
	String * foreground;
};

class DefaultWorldGenerator : AbstractWorldGenerator
{
	String * bg;
	String * map;

public:
	DefaultWorldGenerator();
	~DefaultWorldGenerator();
	void generateForeground();
	void generateBackground();
	void generateMountains();
	void fillGroundLevel();
	void fillGrass();
	void fillRocks();
	void fillTrees();
	String * dispatchForeground();
	String * dispatchBackground();
private:
	static bool randomBoolean(unsigned int percetnage);
	static double noise(int x);
	static double cosineInterpolate(int a, int b, double x);
	void interpolateMap(int x, int peakValue, int prevPeakValue);
	static bool hasBlockNeigh(int y, int x, String * map, char sign);
	
};

class FlatWorldGenerator : AbstractWorldGenerator
{
	String * bg;
	String * map;
	static bool randomBoolean(unsigned int percetnage);
public:
	FlatWorldGenerator();
	~FlatWorldGenerator();
	void generateForeground();
	void generateBackground();
	void generateMountains();
	void fillGroundLevel();
	void fillGrass();
	void fillRocks();
	void fillTrees();
	String * dispatchForeground();
	String * dispatchBackground();
};

class WorldManager {
public:

	Map generateWorld(AbstractWorldGenerator * generator);
};


