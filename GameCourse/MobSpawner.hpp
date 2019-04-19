#pragma once
#include "Enemy.hpp"
#include "WorldDef.h"
#include <time.h>
using namespace std;

//Observer
class MobSpawner : Observer
{
	list<Entity *> * entities;
	int entityCount;
	void genEnemies(int i) {
		
		if (i == 0) return;

		srand(time(0));
		for (int j = 0; j < i; j++)
		{
			
			int x = (rand() % (W-2) ) + 1;
			std::cout << "Spawned! "<< x << std::endl;

			Entity * newEnemy = (rand() % 2) + 1 == 1 ? pig->clone() : zombie->clone();
			newEnemy->addDeathHandler(this);
			moveTo(newEnemy, x * 32, 32 * 12);
			entities->push_back(newEnemy);
		}
	}

	void moveTo(Entity * e, float x, float y) {
		e->setLife(6);
		e->setX(x);
		e->setY(y);
	}
	Enemy * pig;
	Enemy * zombie;
	
public:
	explicit MobSpawner(list<Entity *> * entities) {
		this->entities = entities;
		this->entityCount = W / 10;
		srand(time(0));

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

	void handleEvent(Entity * deletedEntity) {
		Entity * newEntity = deletedEntity->clone();
		int newX = (rand() % (W - 2)) + 1;
		moveTo(newEntity, newX * 32, 32 * 12);
		newEntity->addDeathHandler(this);
		entities->push_back(newEntity);
	}

	void generateRandomEntities(int i) {
		genEnemies(i);
	}

	~MobSpawner() {
		//delete this->pig.getTexture();
		//delete this->enemyAnim.getTexture();
	}
};

