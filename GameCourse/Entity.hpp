#pragma once
#include <SFML/Graphics.hpp>
#include"anim.hpp"
#include <list>

class Entity
{
public:
	float x, y, dx, dy, w, h;
	bool life, dir;
	AnimationManager anim;
	std::string name;

	Entity();
	Entity(AnimationManager &a, int X, int Y);
	virtual void update(float time, String TileMap[]) = 0;
	void draw(RenderWindow &window, float offsetX, float offsetY);
	FloatRect getRect();
	static void entitiesInteraction(std::list<Entity*>  *entities, Entity * player);
	static void deleteAllEntities(std::list<Entity*>  *entities);
	static void updateAllEntities(std::list<Entity*>  *entities, float time, String * TileMap);
	static void drawAllEntities(std::list<Entity*>  *entities, double offsetX, double offsetY, RenderWindow &window);
};

