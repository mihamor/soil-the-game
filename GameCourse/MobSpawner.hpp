#pragma once
#include "Enemy.hpp"
#include "WorldDef.h"
#include <time.h>
using namespace std;
class MobSpawner
{
	list<Entity *> * entities;
	int entityCount;


	AnimationManager enemyAnim;
	AnimationManager zombieAnim;

	int countEnemies() {
		int count = 0;
		for (Entity * en : *entities) {
			if (en->name == "Enemy") {
				count++;
			}
		}
		return count;
	}
	void genEnemies(int i) {
		
		if (i == 0) return;

		srand(time(0));
		for (int j = 0; j < i; j++)
		{
			std::cout << "Spawned!" << std::endl;
			int x = (rand() % (W-2) ) + 1;
			entities->push_back(new Enemy((rand() % 2) + 1 == 1 ? enemyAnim : zombieAnim, x * 32, 32 * 12, false));
		}
	}

public:
	MobSpawner(list<Entity *> * entities) {
		this->entities = entities;
		this->entityCount = W / 10;

		Texture *  enemyT = new Texture();
		Texture * zombieT = new Texture();

		enemyT->loadFromFile("sprites/babypig.png");
		enemyAnim.loadFromXML("sprites/babypig_anim.xml", enemyT);
		zombieT->loadFromFile("sprites/skeleton.png");
		zombieAnim.loadFromXML("sprites/zombie_anim.xml", zombieT);

	}

	void check(int i) {
		genEnemies(i);
	}

	~MobSpawner() {
		delete this->zombieAnim.getTexture();
		delete this->enemyAnim.getTexture();
	}
};

