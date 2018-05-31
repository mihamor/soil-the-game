#pragma once
#include <SFML/Graphics.hpp>
#include"anim.hpp"
#include "Block.hpp"
#include <list>
#include "WorldDef.h"
#include "SoundSystem.hpp"
class Entity
{
public:
	float x, y, dx, dy, w, h;
	int life;
	bool hit;
	bool dir;
	AnimationManager anim;
	std::string name;
	SoundSystem * soundHandler;

	Entity();
	void hitted(bool dir);
	Entity(AnimationManager &a, int X, int Y);
	void flip(bool side) {
		this->anim.flip(side);
	}
	virtual void update(float time, String TileMap[], std::list<AbstractBlock *> blocks ) = 0;
	void draw(RenderWindow &window, float offsetX, float offsetY);
	FloatRect getRect();
	static int entitiesInteraction(std::list<Entity*>  *entities, Entity * player, SoundSystem * soundSystem);
	static void deleteAllEntities(std::list<Entity*>  *entities);
	static void updateAllEntities(std::list<Entity*>  *entities, float time, String * TileMap, std::list<AbstractBlock *> blocks);
	static void drawAllEntities(std::list<Entity*>  *entities, double offsetX, double offsetY, RenderWindow &window);

	bool intersects(Vector2i coords);
};

