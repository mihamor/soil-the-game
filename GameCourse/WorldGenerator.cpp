#include "WorldGenerator.hpp"

bool DefaultWorldGenerator::randomBoolean(unsigned int percetnage) {
	return ((rand() % 100) + 1) <= (int)percetnage;
}
/*String * WorldGenerator::generate() {
	String * newMap = new String[H];
	fillGroundLevel(newMap);
	randMountains(newMap);
	fillGrass(newMap);
	fillRocks(newMap);
	fillTrees(newMap);


	return newMap;
};*/




double DefaultWorldGenerator::noise(int x) {
	x = (x << 13) ^ x;
	return (1.0 - ((x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

double DefaultWorldGenerator::cosineInterpolate(int a, int b, double x){
	double ft = x * 3.1415927;
	double f = (1 - cos(ft)) * .5;
	return  a * (1 - f) + b * f;
}

void DefaultWorldGenerator::generateForeground() {
	this->map = new String[H];
}
void DefaultWorldGenerator::generateBackground() {
	this->bg = new String[H];
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W + 1; x++) {
			if (y > H - groundLevel && y != H - 1) this->bg[y].insert(x, "s");
			else this->bg[y].insert(x, " ");
		}
	}
};

 bool DefaultWorldGenerator::hasBlockNeigh(int y, int x, String * map, char sign) {
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
 void DefaultWorldGenerator::fillGroundLevel() {
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W + 1; x++) {
			//std::string block = DEFAULT_BG_SINGNATURE + "";
			if (x == 0 || x == W - 1) this->map[y].insert(x, "B");
			else if (y > H - groundLevel && y != H - 1) this->map[y].insert(x, "S");
			else if (y == H - 1) this->map[y].insert(x, "B");
			else this->map[y].insert(x, " ");
		}
	}
}

 int mapNumber(int num, int min, int max) {
	 return min + (num % static_cast<int>(max - min + 1));
 }

 void fillToLevel(String * map, int x, int from, int to, char filler) {
	 for (int i = from; i < to; i++) {
		 map[i][x] = filler;
	 }
}

 void DefaultWorldGenerator::interpolateMap(int x, int peakValue, int prevPeakValue) {
	 int leftLimit = x - W / 10;
	 for (int y = 0; y < W / 10; y++) {
		 double interpolationParam = (y / (double)(W / 10));
		 int interpolatedValue = cosineInterpolate(prevPeakValue, peakValue, interpolationParam);
		 this->map[interpolatedValue][leftLimit + y] = 'S';
		 fillToLevel(this->map, leftLimit + y, interpolatedValue, groundLevel + 1, 'S');

	 }
}



void DefaultWorldGenerator::generateMountains() {
	srand((unsigned int)time(0));
	int h = jumpDist;
	int lastRes = jumpDist;
	int prevPeakValue = groundLevel;
	int x = 0;

	for (; x < W; x += W / 10) {
		int peakValue = abs((int)(noise(x) * rand()));
		peakValue = mapNumber(peakValue, groundLevel - jumpDist, groundLevel);
		this->map[peakValue][x] = 'S';
		fillToLevel(this->map, x, peakValue, groundLevel + 1, 'S');

		if (x > 0) {
			interpolateMap(x, peakValue, prevPeakValue);
		}
		prevPeakValue = peakValue;

		//h = (rand() % jumpDist + 1);
		//if ((int)abs(lastRes - h) > jumpDist) h = abs(h - lastRes);
		//lastRes = h;
		//for (int y = 0; y < h; y++) this->map[groundLevel - y][x] = 'S';
	}
	interpolateMap(x, groundLevel, prevPeakValue);
}

void DefaultWorldGenerator::fillGrass() {
	for (int y = 1; y < H - 1; y++) {
		for (int x = 1; x < W - 1; x++) {
			if (this->map[y][x] == ' ' && hasBlockNeigh(y, x, this->map, 'S')) this->map[y][x] = 'G';
		}
	}
}
void DefaultWorldGenerator::fillRocks() {
	for (int x = 1; x < W - 1; x++) {
		int h = (rand() % groundLevel / 4 + groundLevel / 2);
		for (int y = 0; y < h; y++)
		{
			bool placeIron = randomBoolean(10);
			bool placeGold = randomBoolean(5);
			bool placeWolfram = randomBoolean(1);
			if (placeIron) this->map[H - 2 - y][x] = 'I';
			else if (placeGold) this->map[H - 2 - y][x] = 'X';
			else if (placeWolfram) this->map[H - 2 - y][x] = 'Y';
			else this->map[H - 2 - y][x] = 'R';
		}
	}
}
void DefaultWorldGenerator::fillTrees() {
	int treesCount = W / 10;
	int j = 0;
	int i = 0;
	while (j < treesCount && i < 100000) {
		for (int y = groundLevel - jumpDist; y < groundLevel + jumpDist; y++) {
			int x = (rand() % (W - 1)) + 1;
			if (this->map[y][x] == ' ' && hasBlockNeigh(y, x, this->map, 'G')) {
				TreeBlock::placeTree(y, x, this->map);
				j++;
			}
		}
		i++;
	}
}

String * DefaultWorldGenerator::dispatchForeground()
{
	return this->map;
}

String * DefaultWorldGenerator::dispatchBackground()
{
	return this->bg;
}



DefaultWorldGenerator::DefaultWorldGenerator()
{
}

DefaultWorldGenerator::~DefaultWorldGenerator()
{
}

Map WorldManager::generateWorld(AbstractWorldGenerator * generator)
{
	generator->generateBackground();
	generator->generateForeground();
	generator->fillGroundLevel();
	generator->generateMountains();
	generator->fillGrass();
	generator->fillRocks();
	generator->fillTrees();

	Map newMap;
	newMap.background = generator->dispatchBackground();
	newMap.foreground = generator->dispatchForeground();

	return newMap;
}
