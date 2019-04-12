#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "WorldDef.h"
using namespace sf;


// bridge
class AbstractWeapon : public Entity {
protected:
	int damage;
public:
	virtual void update(float time, String TileMap[], std::list<AbstractBlock *> blocks) = 0;
	virtual int getDamage() = 0;
	virtual Entity * clone() = 0;
};


class ContextWeapon : public AbstractWeapon {
	AbstractWeapon * weapon;
public:
	ContextWeapon(AbstractWeapon * weapon) {
		this->weapon = weapon;
		this->name = weapon->name;
	}
	~ContextWeapon(){
		if (!weapon) delete weapon;
	}
	void update(float time, String TileMap[], std::list<AbstractBlock *> blocks) { this->weapon->update(time, TileMap, blocks); }
	Entity * clone() { return this->weapon->clone(); }
	int getDamage() { return this->weapon->getDamage(); }
	void draw(RenderWindow &window, float offsetX, float offsetY) { this->weapon->draw(window, offsetX, offsetY); }
	float getX() { return this->weapon->getX(); }
	float getY() { return this->weapon->getY(); }
	float getDx() { return this->weapon->getDx(); }
	void flip(bool side) { this->weapon->flip(side); }
	float getDy() { return this->weapon->getDy(); }
	float getWeight() { return this->weapon->getWeight(); }
	float getHeight() { return this->weapon->getHeight(); }
	bool isAlive() { return this->weapon->isAlive(); }
	std::string getName() { return this->weapon->getName(); }
	FloatRect getRect() { return this->weapon->getRect(); }


	void setX(float value) { this->weapon->setX(value); }
	void setY(float value) { this->weapon->setY(value); }
	bool isOver() { return this->weapon->isOver(); }
	void setLife(int value) { this->weapon->setLife(value); }
	bool getDir() { return this->weapon->getDir();; }
};





class Bullet : public AbstractWeapon
{
public:
	Bullet(AnimationManager a, int X, int Y, bool side);
	~Bullet();
	void update(float time, String TileMap[], std::list<AbstractBlock *> blocks);
	Entity * clone();
	int getDamage();
};
class Sword : public AbstractWeapon
{
public:
	Sword(AnimationManager a, int X, int Y, bool side);
	~Sword();
	void update(float time, String TileMap[], std::list<AbstractBlock *> blocks);
	Entity * clone();
	int getDamage();
};