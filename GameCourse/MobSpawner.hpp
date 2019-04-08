#pragma once
#include "Enemy.hpp"
#include "WorldDef.h"
#include <time.h>
using namespace std;
class MobSpawner
{
	list<Entity *> * entities;
	int entityCount;
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

			Entity * newEnemy = (rand() % 2) + 1 == 1 ? pig->clone() : zombie->clone();
			moveTo(newEnemy, x * 32, 32 * 12);
			entities->push_back(newEnemy);
		}
	}

	void moveTo(Entity * e, float x, float y) {
		e->x = x;
		e->y = y;
	}


	Enemy * pig;
	Enemy * zombie;
	
public:
	MobSpawner(list<Entity *> * entities) {
		this->entities = entities;
		this->entityCount = W / 10;

		Texture *  enemyT = new Texture();
		Texture * zombieT = new Texture();
		enemyT->loadFromFile("sprites/babypig.png");
		//enemyAnim.loadFromXML("sprites/babypig_anim.xml", enemyT);
		zombieT->loadFromFile("sprites/skeleton.png");
		//zombieAnim.loadFromXML("sprites/zombie_anim.xml", zombieT);

		auto animationPig = *Entity::factory.getAnimationManager("sprites/babypig_anim.xml", enemyT);
		auto animationZombie = *Entity::factory.getAnimationManager("sprites/zombie_anim.xml", zombieT);

		pig = new Enemy(animationPig, 0, 0, true);
		zombie = new Enemy(animationZombie, 0, 0, true);
	}

	void check(int i) {
		genEnemies(i);
	}

	~MobSpawner() {
		//delete this->pig.getTexture();
		//delete this->enemyAnim.getTexture();
	}
};

