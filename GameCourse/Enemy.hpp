#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#define SFML_DYNAMIC

using namespace sf;
class Enemy:public Entity
{
	bool onGround, shoot, hit;
	enum { stay, walk, playerDetected} STATE;
public:

	Enemy(AnimationManager a, int X, int Y, bool dir);
	~Enemy();
	void update(float time, String TileMap[]);
	void Collision(int num, String TileMap[]);
};
