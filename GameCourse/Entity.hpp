#pragma once
#include <SFML/Graphics.hpp>
#include "Block.hpp"
#include <list>
#include "WorldDef.h"
#include "SoundSystem.hpp"
#include "AnimationFactory.hpp"

// prototype

class Entity;

class Observer {
public:
	virtual void handleEvent(Entity * deletedEntity) = 0;
};

class Entity
{
protected:
	Observer *  _observer = NULL;
	void _Notify()
	{
		std::cout << _observer << std::endl;
		if(_observer) _observer->handleEvent(this);
	}
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
	void kill() { _Notify(); }
	void addDeathHandler(Observer * ref){
		std::cout << "added observer: "<< ref << std::endl;
		_observer = ref;
	}
	virtual void setX(float value) { x = value; }
	virtual void setY(float value) { y = value; }
	virtual void setDx(float value) { dx = value; }
	virtual void setDy(float value) { dy = value; }
	virtual void setDir(bool value) { dir = value; }
	virtual void setAnimationManager(AnimationManager value) { anim = value; }


	virtual bool isOver() { return anim.isOver(); }
	virtual void setLife(int value) { life = value; }
	virtual bool getDir() { return dir; }


	virtual SoundSystem * getSoundHandler() { return soundHandler; }
	virtual float getX() { return x; }
	virtual float getY() { return y; }
	virtual float getDx() { return dx; }
	virtual float getDy() { return dy; }
	virtual float getWeight() { return w; }
	virtual float getHeight() { return h; }
	virtual AnimationManager * getAnimationManager() { return &anim; }
	virtual bool isAlive() { return life; }
	virtual std::string getName() { return name; }
	virtual FloatRect getRect();
	
	virtual void update(float time, String TileMap[], std::list<AbstractBlock *> blocks ) = 0;
	virtual Entity * clone() = 0;
	virtual void draw(RenderWindow &window, float offsetX, float offsetY);
	bool intersects(Vector2i coords, float offsetX, float offsetY);
};