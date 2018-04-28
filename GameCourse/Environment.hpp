#pragma once
#include "Block.hpp"
#include "Enemy.hpp"
#include "PLAYER.hpp"
#include <list>
#include "Bullet.hpp"
#include "Inventory.hpp"
#include "Cursor.hpp"
#include "tilemap.h"
const int INV_SIZE = 10;

using namespace sf;
class Environment
{

	Player * p;
	std::list<Block *> * blocks;
	std::list<Entity *>  * entities;
	Inventory * inv;
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
	Environment(int vmodex, int vmodey) {
		this->vmodex = vmodex;
		this->vmodey = vmodey;
		TMap::loadTileMap("map.mf", TileMap);
		TMap::loadTileMap("mapbg.mf", TileMapBg);

		Texture * playerT = new Texture();
		Texture *  enemyT = new Texture();
		playerT->loadFromFile("sprites/willy.png");
		enemyT->loadFromFile("sprites/babypig.png");
		anim.loadFromXML("sprites/willy_anim.xml", playerT);
		enemyAnim.loadFromXML("sprites/babypig_anim.xml", enemyT);
		this->p = new Player(anim, 64, 64);
		const int MAX_SIZE = 10;
		inv = new Inventory(MAX_SIZE);

		this->entities = new std::list<Entity *>();
		this->entities->push_back(p);
		this->entities->push_back(new Enemy(enemyAnim, 32 * (W - 1), 32 * 12, false));
		this->entities->push_back(new Enemy(enemyAnim, 32 * (W - W / 2), 32 * 12, true));


		this->blocks = new std::list<Block *>();
		Texture * rockT = new Texture();
		rockT->loadFromFile("blocks/rock.png");
		Block * rock = new Block(rockT, 'R', Solid);

		Texture * bgrockT = new Texture();
		bgrockT->loadFromFile("blocks/bgrock.png");
		Block * bgrock = new Block(bgrockT, '-', Background);


		Texture *  bgT = new Texture();
		bgT->loadFromFile("blocks/bg.png");
		Block * bg = new Block(bgT, ' ', Background);

		Texture * bedrockT  = new Texture();
		bedrockT->loadFromFile("blocks/bedrock.png");
		Block *  bedrock = new Block(bedrockT, 'B', Solid);


		Texture *groundT = new Texture();
		groundT->loadFromFile("blocks/ground.png");
		Block * ground = new Block(groundT, 'G', Solid);

		Texture *soilT = new Texture();
		soilT->loadFromFile("blocks/soil.png");
		Block * soil = new Block(soilT, 'S', Solid);

		this->blocks->clear();

		this->blocks->push_back(bedrock);
		this->blocks->push_back(bg);
		this->blocks->push_back(rock);
		this->blocks->push_back(bgrock);
		this->blocks->push_back(ground);
		this->blocks->push_back(soil);

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
		TMap::removeBlock(p, a.x, a.y, offsetX, offsetY, *blocks, TileMap, TileMapBg, *inv);
	}
	bool isInvGui() {
		return isGui;
	}
	void addBlock(Vector2i a) {
		int posx = (a.x + (int)offsetX) / 32;
		int posy = (a.y + (int)offsetY) / 32;
		Block * check = Block::getBlock(*blocks, TileMap, posy, posx);
		if (check == NULL || check->singnature == DEFAULT_BG_SINGNATURE) p->setHand(NULL);
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
			Entity::updateAllEntities(entities, time, TileMap);

		// сдвиг карты при движение view.setCenter(p->x, p->y); window.setView(view)

		if (p->x > vmodex / 2 && p->x< (vmodex + 32 * W) / 2) offsetX = p->x - vmodex / 2;
		if (p->y > vmodey / 2 && p->y + offsetY < 32 * H) offsetY = p->y - vmodey / 2;

		// отрисовка общего задника
		//window.draw(surface);
		// отрисовка блоков
		window.clear(Color(255, 255, 255));
		Block::drawViewField(blocks, TileMap, TileMapBg, offsetX, offsetY, H, W, window);
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
			Block * b = *it;
			it = blocks->erase(it);
			delete b->rectangle.getTexture();
			delete b;
		}
		delete blocks;

		TMap::saveTileMap("map.mf", TileMap);
		TMap::saveTileMap("mapbg.mf", TileMapBg);
		inv->saveInventory();

		delete anim.getTexture();
		delete enemyAnim.getTexture();

	}


};

