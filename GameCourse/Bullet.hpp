#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "WorldDef.h"
using namespace sf;
class Bullet :public Entity
{
private:
	WeaponType wtype;
public:
	Bullet(AnimationManager a, int X, int Y, bool side, WeaponType wtype);
	~Bullet();
	void update(float time, String TileMap[], std::list<AbstractBlock *> blocks);
};