#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
using namespace sf;
class Bullet:public Entity
{
public:
	Bullet(AnimationManager a, int X, int Y, bool side);
	~Bullet();
	void update(float time, String TileMap[], std::list<AbstractBlock *> blocks);
};