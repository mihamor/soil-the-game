#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#define SFML_DYNAMIC

using namespace sf;
class Enemy:public Entity
{
	bool onGround, shoot;
	enum { stay, walk, playerDetected} STATE;
public:

	Enemy(AnimationManager a, int X, int Y, bool dir);
	~Enemy();
	void update(float time, String TileMap[], std::list<AbstractBlock *> blocks);
	void Collision(int num, String TileMap[], std::list<AbstractBlock *> & blocks);
};

