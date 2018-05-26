#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

using namespace sf;
class Enemy:public Entity
{
	bool onGround, shoot;
	enum { stay, walk, playerDetected} STATE;
	Vector2i initPosition;

	void normalizePosition();

public:

	Enemy(AnimationManager a, int X, int Y, bool dir);
	~Enemy();
	void update(float time, String TileMap[], std::list<AbstractBlock *> blocks);
	void Collision(int num, String TileMap[], std::list<AbstractBlock *> & blocks);
};

