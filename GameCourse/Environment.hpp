#pragma once
#include "Enemy.hpp"
#include "PLAYER.hpp"
#include <list>
#include "Bullet.hpp"
#include "BlockPackage.h"
#include "WorldGenerator.hpp"
#include "Inventory.hpp"
#include <iostream>
#include "Workbench.hpp"
#include <map>
#include "Cursor.hpp"
#include "LightHandler.hpp"


const int INV_SIZE = 10;
const Vector2i startPlayerPos(16*W,64);
using namespace sf;
class Environment
{
	Player * p;
	std::list<AbstractBlock *> * blocks;
	std::list<Entity *>  * entities;
	Inventory * inv;
	int menuChoice;
	float offsetX = 0, offsetY = 0;
	GameCursor cursor;
	bool isGuiInv = false;
	bool isGuiWorkbench = false;
	String TileMap[H];
	String TileMapBg[H];

	HudItems hItems;
	
	std::map<std::string, Workbench *> wbenches;
	std::string wbTrigger;

	int vmodex, vmodey;
	int slot;
	AnimationManager anim;
	AnimationManager enemyAnim;

	//light

	LightHandler * ls;

	

public:


	Environment(int vmodex, int vmodey, int choice, int slot, RenderWindow & window);
	Player * player();

	std::list<AbstractBlock *> * blocksList();
	std::list<Entity *>  * entitiesList();
	void addBullet();
	void setGuiInv(bool state);
	void setGuiWorkbench(bool state, std::string trigger = 0);
	void setBlock(Vector2i a);
	void removeBlock(Vector2i a);
	bool isInvGui();
	bool isWorkbenchGui();
	bool isGui();
	void addBlock(Vector2i a);
	auto inventory();
	bool isRange(Vector2i a);
	Vector2i offset();
	void update(float time, RenderWindow &window, sf::Vector2i a);
	~Environment();

private:
	
	void initMap();
	static void drawViewField(std::list<AbstractBlock*> * blocks, String * TileMap, String * TileMapBg, double offsetX, double offsetY, RenderWindow & window, int vmodex, int vmodey);


};

