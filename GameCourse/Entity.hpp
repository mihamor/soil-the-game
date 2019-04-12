#pragma once
#include <SFML/Graphics.hpp>
#include "Block.hpp"
#include <list>
#include "WorldDef.h"
#include "SoundSystem.hpp"
#include "AnimationFactory.hpp"

// prototype


class Entity
{
public:
	static AnimationFactory factory;
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
	virtual void flip(bool side) {
		this->anim.flip(side);
	}
	virtual void setX(float value) { x = value; }
	virtual void setY(float value) { y = value; }
	virtual bool isOver() { return anim.isOver(); }
	virtual void setLife(int value) { life = value; }
	virtual bool getDir() { return dir; }




	virtual float getX() { return x; }
	virtual float getY() { return y; }
	virtual float getDx() { return dx; }
	virtual float getDy() { return dy; }
	virtual float getWeight() { return w; }
	virtual float getHeight() { return h; }
	virtual bool isAlive() { return life; }
	virtual std::string getName() { return name; }
	virtual FloatRect getRect();
	
	virtual void update(float time, String TileMap[], std::list<AbstractBlock *> blocks ) = 0;
	virtual Entity * clone() = 0;
	virtual void draw(RenderWindow &window, float offsetX, float offsetY);
	


	static int entitiesInteraction(std::list<Entity*>  *entities, Entity * player, SoundSystem * soundSystem);
	static void deleteAllEntities(std::list<Entity*>  *entities);
	static void updateAllEntities(std::list<Entity*>  *entities, float time, String * TileMap, std::list<AbstractBlock *> blocks);
	static void drawAllEntities(std::list<Entity*>  *entities, double offsetX, double offsetY, RenderWindow &window);

	bool intersects(Vector2i coords, float offsetX, float offsetY);
};