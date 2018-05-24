#pragma once
#include "Enemy.hpp"
#include "PLAYER.hpp"
#include <list>
#include "Bullet.hpp"
#include "BlockLoader.h"
#include "WorldGenerator.hpp"
#include "Inventory.hpp"
#include <iostream>
#include "Workbench.hpp"
#include <map>
#include "Cursor.hpp"
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
	
	std::map<std::string, Workbench *> wbenches;
	std::string wbTrigger;

	int vmodex, vmodey;
	int slot;
	AnimationManager anim;
	AnimationManager enemyAnim;

	void initMap() {
		for(int y = 0; y < H; y++)
			for (int x = 0; x < W; x++) {
				TileMap[y].insert(0, " ");
				TileMapBg[y].insert(0, " ");
			}
	}

public:


	Environment(int vmodex, int vmodey, int choice, int slot) {
		this->vmodex = vmodex;
		this->vmodey = vmodey;
		this->menuChoice = choice;
		this->slot = slot;

		initMap();
		if (choice == 1) {
			if (!TMap::loadTileMapFromSlot(slot, TileMap, TileMapBg)) assert(0 && "Invalid slot");
		}
		else {
			WorldGenerator gen;
			String * generatedBg = gen.getBg();
			String * generated = gen.getMap();
			TMap::copyFrom(generated, TileMap);
			TMap::copyFrom(generatedBg, TileMapBg);
		}
		

		Texture * playerT = new Texture();
		Texture *  enemyT = new Texture();
		playerT->loadFromFile("sprites/willy.png");
		//playerT->loadFromFile("sprites/megaman.png");
		enemyT->loadFromFile("sprites/babypig.png");
		anim.loadFromXML("sprites/willy_anim.xml", playerT);
		//anim.loadFromXML("sprites/anim_megaman.xml", playerT);
		enemyAnim.loadFromXML("sprites/babypig_anim.xml", enemyT);
		this->p = new Player(anim, startPlayerPos.x, startPlayerPos.y);
		const int MAX_SIZE = 15;
		inv = new Inventory(MAX_SIZE);

		this->entities = new std::list<Entity *>();
		this->entities->push_back(p);
		this->entities->push_back(new Enemy(enemyAnim, 32 * (W - 1), 32 * 12, false));
		this->entities->push_back(new Enemy(enemyAnim, 32 * (W - W / 2), 32 * 12, true));

		this->blocks = BlockLoader::loadBlocksFromXml("blocks.xml");


		wbenches["player"] = new Workbench(inv, *blocks, "recipes/player.xml");
		wbenches["workbench"] = new Workbench(inv, *blocks, "recipes/workbench.xml");
		wbenches["furnace"] = new Workbench(inv, *blocks, "recipes/furnace.xml");
	};

	Player * player() {
		return this->p;
	};

	auto blocksList() {
		return this->blocks;
	}

	auto entitiesList() {
		return this->entities;
	}
	void addBullet() {
		entities->push_back(new Bullet(anim, p->x + p->w / 2, p->y + p->h / 4, p->dir));
	}

	void setGuiInv(bool state) {
		isGuiInv = state;
	}

	void setGuiWorkbench(bool state, std::string trigger = 0) {
		isGuiWorkbench = state;
		this->wbTrigger = trigger;
	}
	void setBlock(Vector2i a) {
		int posx = (a.x + (int)offsetX) / 32;
		int posy = (a.y + (int)offsetY) / 32;
		AbstractBlock * bl = AbstractBlock::getBlock(*blocks, TileMap, posy, posx);
		if (!TMap::setBlock(p, a.x, a.y, offsetX, offsetY, *blocks, TileMap, TileMapBg, *inv)) {
			if (bl->interact() == doorType) {
				DoorBlock * db = (DoorBlock *)bl;
				std::cout << "Now type is " << (db->doorUse(posx, posy, this->TileMap) != Solid ? "SOLID" : "BACKGROUND") << std::endl;
			}
			if (bl->interact() == craftType) {
				WorkbenchBlock * wb = (WorkbenchBlock *)bl;
				std::cout << "Craft opening " << wb->getId() << std::endl;
				setGuiWorkbench(true, wb->getId());
			}
		}
	}
	void removeBlock(Vector2i a) {
		int posx = (a.x + (int)offsetX) / 32;
		int posy = (a.y + (int)offsetY) / 32;
		AbstractBlock * bl = AbstractBlock::getBlock(*blocks, TileMap, posy, posx);
		if(bl->interact() == removeType)
			TMap::removeBlock(p, a.x, a.y, offsetX, offsetY, *blocks, TileMap, TileMapBg, *inv);
		else if (bl->interact() == doorType) {
			TMap::removeBlock(p, a.x, a.y, offsetX, offsetY, *blocks, TileMap, TileMapBg, *inv);
		}
		else if (bl->interact() == treeType) {
			TMap::removeBlock(p, a.x, a.y, offsetX, offsetY, *blocks, TileMap, TileMapBg, *inv);
		}else TMap::removeBlock(p, a.x, a.y, offsetX, offsetY, *blocks, TileMap, TileMapBg, *inv);
		std::cout << "Interaction " << bl->interact() << std::endl;
	}
	bool isInvGui() {
		return isGuiInv;
	}

	bool isWorkbenchGui() {
		return isGuiWorkbench;
	}

	bool isGui(){
	 return isGuiInv || isGuiWorkbench;
	}
	void addBlock(Vector2i a) {
		int posx = (a.x + (int)offsetX) / 32;
		int posy = (a.y + (int)offsetY) / 32;
		AbstractBlock * check = AbstractBlock::getBlock(*blocks, TileMap, posy, posx);
		if (check == NULL || check->singnature == DEFAULT_BG_SINGNATURE) {
			check = AbstractBlock::getBlock(*blocks, TileMapBg, posy, posx);
			if (check == NULL || check->singnature == DEFAULT_BG_SINGNATURE) p->setHand(NULL);
			else inv->addSlot(check);
		}
		else inv->addSlot(check);
	}
	auto inventory() {
		return this->inv;
	}
	bool isRange(Vector2i a) {
		return p->isInRange(a.x, a.y, offsetX, offsetY);
	}

	Vector2i offset() {
		return Vector2i(offsetX, offsetY);
	}

	void update(float time, RenderWindow &window, sf::Vector2i a) {
		this->cursor.update(isRange(a), a, time);
		// взаемодействие динамических обьектов
		Entity::entitiesInteraction(entities, p);
		// апдейт динамических обьектов
		if (!isGui())
			Entity::updateAllEntities(entities, time, TileMap, *blocks);

		// сдвиг карты при движение 
		/*
		View view;
		view.setCenter(p->x, p->y);
		view.setSize(Vector2f(vmodex, vmodey));
		window.setView(view);*/

		if (p->x > vmodex / 2 && p->x  <  W*(32) - vmodex / 2) offsetX = p->x - vmodex / 2;
		if (p->y > vmodey / 2 && p->y  < H*(32) - vmodey / 2) offsetY = p->y - vmodey / 2;

		// отрисовка общего задника
		//window.draw(surface);
		// отрисовка блоков
		//if(p->isMoving())window.clear(Color(255, 255, 255));

		AbstractBlock::drawViewField(blocks, TileMap, TileMapBg, offsetX, offsetY, H, W, window, vmodex, vmodey);
		// отрисовка сущностей
		Entity::drawAllEntities(entities, offsetX, offsetY, window);
		// отрисовка курсора

		//Отрисовка HUD
		p->drawHUD(window, vmodex, vmodey);
		//отрисовка инвентаря(ставить последним)
		if (isGuiInv)
			this->inv->draw(vmodex, vmodey, window, &isGuiInv, &a, p);
		else if (isGuiWorkbench)
			this->wbenches[wbTrigger]->draw(window, vmodey, vmodex, &isGuiWorkbench);
		
		cursor.draw(window);
	}

	~Environment() {
		Entity::deleteAllEntities(entities);
		delete entities;


		while (!this->blocks->empty()) {
			auto it = blocks->begin();
			AbstractBlock * b = *it;
			it = blocks->erase(it);
			delete b->rectangle.getTexture();
			delete b;
		}
		delete blocks;


		TMap::saveTileMapToSlot(slot, TileMap, TileMapBg);
		inv->saveInventory();
		//wb->workbenchSave("");

		delete anim.getTexture();
		delete enemyAnim.getTexture();
		delete wbenches["player"];
		delete wbenches["workbench"];
		delete wbenches["furnace"];
	}


};

