#pragma once
#include "Enemy.hpp"
#include "PLAYER.hpp"
#include <list>
#include "Bullet.hpp"
#include "BlockLoader.h"
#include "WorldGenerator.hpp"
#include "Inventory.hpp"
#include <iostream>
#include "Cursor.hpp"
const int INV_SIZE = 10;

using namespace sf;
class Environment
{

	Player * p;
	std::list<AbstractBlock *> * blocks;
	std::list<Entity *>  * entities;
	Inventory * inv;
	int menuChoice;
	float offsetX = 0, offsetY = 0;
	Cursor cursor;
	bool isGui = false;
	String TileMap[H] =
	{
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
	};
	String TileMapBg[H] =
	{
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
	};

	int vmodex, vmodey;
	AnimationManager anim;
	AnimationManager enemyAnim;

public:
	Environment(int vmodex, int vmodey, int choice) {
		this->vmodex = vmodex;
		this->vmodey = vmodey;
		this->menuChoice = choice;
		if (choice == 1) {
			TMap::loadTileMap("map.mf", TileMap);
			TMap::loadTileMap("mapbg.mf", TileMapBg);
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
		this->p = new Player(anim, 64, 64);
		const int MAX_SIZE = 10;
		inv = new Inventory(MAX_SIZE);

		this->entities = new std::list<Entity *>();
		this->entities->push_back(p);
		this->entities->push_back(new Enemy(enemyAnim, 32 * (W - 1), 32 * 12, false));
		this->entities->push_back(new Enemy(enemyAnim, 32 * (W - W / 2), 32 * 12, true));

		this->blocks = BlockLoader::loadBlocksFromXml("blocks.xml");

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

	void setGui(bool state) {
		isGui = state;
	}
	void setBlock(Vector2i a) {
		TMap::setBlock(p, a.x, a.y, offsetX, offsetY, *blocks, TileMap, TileMapBg, *inv);
	}
	void removeBlock(Vector2i a) {
		int posx = (a.x + (int)offsetX) / 32;
		int posy = (a.y + (int)offsetY) / 32;
		AbstractBlock * bl = AbstractBlock::getBlock(*blocks, TileMap, posy, posx);
		if(bl->interact() == removeType)
			TMap::removeBlock(p, a.x, a.y, offsetX, offsetY, *blocks, TileMap, TileMapBg, *inv);
		else if (bl->interact() == doorType) {
			DoorBlock * db = (DoorBlock *)bl;
			std::cout << "Now type is " <<  (db->doorUse(posx, posy, this->TileMap) != Solid ? "SOLID" : "BACKGROUND") << std::endl;
		}
		std::cout << "Interaction " << bl->interact() << std::endl;
	}
	bool isInvGui() {
		return isGui;
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
		this->cursor.update(isRange(a), a);
		// взаемодействие динамических обьектов
		Entity::entitiesInteraction(entities, p);
		// апдейт динамических обьектов
		if (!isGui)
			Entity::updateAllEntities(entities, time, TileMap, *blocks);

		// сдвиг карты при движение view.setCenter(p->x, p->y); window.setView(view)

		if (p->x > vmodex / 2 && p->x< (vmodex + 32 * W) / 2) offsetX = p->x - vmodex / 2;
		if (p->y > vmodey / 2 && p->y + offsetY < 32 * H) offsetY = p->y - vmodey / 2;

		// отрисовка общего задника
		//window.draw(surface);
		// отрисовка блоков
		window.clear(Color(255, 255, 255));
		AbstractBlock::drawViewField(blocks, TileMap, TileMapBg, offsetX, offsetY, H, W, window);
		// отрисовка сущностей
		Entity::drawAllEntities(entities, offsetX, offsetY, window);
		// отрисовка курсора

		//Отрисовка HUD
		p->drawHUD(window, vmodex, vmodey);
		//отрисовка инвентаря(ставить последним)
		if (isGui)
			this->inv->draw(vmodex, vmodey, window, &isGui, &a, p);
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

		if (this->menuChoice == 1) {
			TMap::saveTileMap("map.mf", TileMap);
			TMap::saveTileMap("mapbg.mf", TileMapBg);
		}
		inv->saveInventory();

		delete anim.getTexture();
		delete enemyAnim.getTexture();

	}


};

