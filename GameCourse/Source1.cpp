#include <SFML/Graphics.hpp>
#include <iostream>
#include "Enemy.hpp"
#include <list>
#include "Windows.h"
#include <Math.h>
#include "PLAYER.hpp"
#include "tilemap.h"
#include <assert.h>
#include "Bullet.hpp"
#include "Inventory.hpp"
#include "Block.hpp"
#define SFML_DYNAMIC

#pragma comment(lib, "sfml-graphics-s-d.lib")

using namespace sf;



void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
}
//const int ground = 32 * 18;
int vmodex = 600;
int vmodey = 32 * 12;
float offsetX = 0, offsetY = 0;

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

int main()
{	Texture rockT;
	rockT.loadFromFile("blocks/rock.png");
	Block rock(&rockT, 'R', Solid);

	Texture bgrockT;
	bgrockT.loadFromFile("blocks/bgrock.png");
	Block bgrock(&bgrockT, '-', Background);


	Texture bgT;
	bgT.loadFromFile("blocks/bg.png");
	Block bg(&bgT, ' ', Background);

	Texture bedrockT;
	bedrockT.loadFromFile("blocks/bedrock.png");
	Block  bedrock(&bedrockT, 'B', Solid);

	Texture backGroundT;
	backGroundT.loadFromFile("blocks/bgsky.png");
	RectangleShape surface(Vector2f(vmodex, vmodey));
	surface.setTexture(&backGroundT);

	Texture groundT;
	groundT.loadFromFile("blocks/ground.png");
	Block  ground(&groundT, 'G', Solid);

	Texture soilT;
	soilT.loadFromFile("blocks/soil.png");
	Block soil(&soilT, 'S', Solid);
	
	std::list<Block*> blocks;
	blocks.clear();

	blocks.push_back(&bedrock);
	blocks.push_back(&bg);
	blocks.push_back(&rock);
	blocks.push_back(&bgrock);
	blocks.push_back(&ground);
	blocks.push_back(&soil);
	

	RenderWindow window(VideoMode(vmodex, vmodey), "Miha game");
	bool gameOver = false;
	bool Resized = false;
	bool isGui = false;

	TMap::loadTileMap("map.mf", TileMap);
	TMap::loadTileMap("mapbg.mf", TileMapBg);

	bool viewCursor = true;
	Texture c;
	c.loadFromFile("cursor.png");
	RectangleShape * cursor = new RectangleShape(Vector2f(32, 32));


	Texture playerT;
	Texture enemyT;
	//playerT.loadFromFile("sprites/fang.png");
	playerT.loadFromFile("sprites/willy.png");
	enemyT.loadFromFile("sprites/babypig.png");
	//playerT.loadFromFile("sprites/megaman.png");
	// загрузка спрайтов из файла
	

	// разметка анимации
	AnimationManager anim;
	AnimationManager EnemyAnim;
	
	/*anim.create("walk", playerT, 0, 244, 40, 50, 6, 0.005, 40);
	anim.create("jump", playerT, 0, 528, 29, 30, 4, 0.0045, 38);
	anim.create("duck", playerT, 0, 406, 80, 50, 1, 0.005, 0);
	anim.create("stay", playerT, 0, 187, 42, 52, 3, 0.002, 42);
	anim.create("shoot", playerT, 0, 572, 45, 52, 5, 0.004, 45);
	anim.create("shootAndWalk", playerT, 0, 898, 45, 52, 5, 0.005, 50);
	anim.create("explode", playerT, 380, 582, 15, 15, 1, 0.005, 0);
	anim.create("move", playerT, 248, 582, 15, 15, 1, 0.005, 0);*/

	//AnimationManager anim;
	anim.loadFromXML("sprites/willy_anim.xml", &playerT);
	//anim.loadFromXML("sprites/anim_megaman.xml", &playerT);
	EnemyAnim.loadFromXML("sprites/babypig_anim.xml", &enemyT);

	Clock clock;
	View view;
	std::list<Entity*> entities;
	std::list<Entity*>::iterator it;
	// добавление игрока в список
	Player *p = new Player(anim, 64, 64);
	//anim.set("stay");
	// добавление инвентаря
	const int MAX_SIZE = 10;
	Inventory inv(MAX_SIZE);
	entities.push_back(p);
	// добавление врагов в ручную
	entities.push_back(new Enemy(EnemyAnim, 32 * (W - 1), 32*12, false));
	entities.push_back(new Enemy(EnemyAnim, 32 * (W - W / 2), 32*12, true));

	// определение блоков в игре
	RectangleShape rectangle;
	sf::Vector2i a(0, 0);
	while (window.isOpen() && p->life) {
		float time = clock.getElapsedTime().asMicroseconds(); // тик рейт
		clock.restart();
		time = time / 400; // делитель ~  задержка милисекунды
		if (!Resized)
		{
			a = Mouse::getPosition(window);
			if (p->isInRange(a.x, a.y, offsetX, offsetY))
			{
				cursor = new RectangleShape(Vector2f(32, 32));
				cursor->setTexture(&c);
				cursor->setPosition(a.x, a.y);
				viewCursor = true;
			}
		}
		else
			a = Mouse::getPosition();
		// контроль нажатия клавиш
		if (!isGui) {
			if (Keyboard::isKeyPressed(Keyboard::A))
				p->key["L"] = true;
			if (Keyboard::isKeyPressed(Keyboard::D))
				p->key["R"] = true;
			if (Keyboard::isKeyPressed(Keyboard::W))
				p->key["Up"] = true;
			if (Keyboard::isKeyPressed(Keyboard::S))
				p->key["Down"] = true;
			if (Keyboard::isKeyPressed(Keyboard::Space))
				p->key["Space"] = true;
			if (Keyboard::isKeyPressed(Keyboard::E) && a.x <= vmodex && a.y <= vmodey) // взять блок
			{
				int posx = (a.x + (int)offsetX) / 32;
				int posy = (a.y + (int)offsetY) / 32;
				Block * check = Block::getBlock(blocks, TileMap, posy, posx);
				if (check == NULL || check->singnature == bg.singnature) p->setHand(NULL);
				else inv.addSlot(check);
			}
		}
		// call inventory
		if (Keyboard::isKeyPressed(Keyboard::I))
			isGui = true;

		// контроль нажатия крестика на панели окна
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				Entity::deleteAllEntities(&entities);
				TMap::saveTileMap("map.mf", TileMap);
				TMap::saveTileMap("mapbg.mf", TileMapBg);
				inv.saveInventory();
				return EXIT_SUCCESS;
			}
			if (event.type == Event::Resized)
			{
				vmodex = event.size.width;
				vmodey = event.size.height;
				window.create(sf::VideoMode(vmodex, vmodey, 32), "SFML Window");
			}
			if (event.type == Event::KeyPressed && !isGui)
				switch (event.key.code)
				{
				case Keyboard::Space :{
					entities.push_back(new Bullet(anim, p->x + p->w / 2, p->y + p->h / 4, p->dir));
					break;
				}
				default:
					break;
				}
			if(event.type == Event::MouseButtonPressed && !isGui)
				switch (event.key.code)
				{
				case Mouse::Right: { // поставить блок
					TMap::setBlock(p, a.x, a.y, offsetX, offsetY, blocks, TileMap, TileMapBg, inv);
					break;
				}
				case Mouse::Left: { // удалить блок
					TMap::removeBlock(p, a.x, a.y, offsetX, offsetY, blocks, TileMap, TileMapBg, inv);
					break;
				}
				default:
					break;
				}
				
		}

		// взаемодействие динамических обьектов
		Entity::entitiesInteraction(&entities, p);
		// апдейт динамических обьектов
		if (!isGui)
			Entity::updateAllEntities(&entities, time, TileMap);

		// сдвиг карты при движение view.setCenter(p->x, p->y); window.setView(view)

		if (p->x > vmodex / 2 && p->x< (vmodex+32*W)/2) offsetX = p->x - vmodex / 2;
		if (p->y > vmodey / 2 && p->y + offsetY < 32* H) offsetY = p->y - vmodey / 2;

		// отрисовка общего задника
		window.draw(surface);
		// отрисовка блоков
		window.clear(Color(255, 255, 255));
		Block::drawViewField(&blocks, TileMap, TileMapBg, offsetX, offsetY, H, W, window);
		// отрисовка сущностей
		Entity::drawAllEntities(&entities, offsetX, offsetY, window);
		// отрисовка курсора
		if (viewCursor)
		{
			if (cursor != NULL)
			{
				window.draw(*cursor);
				delete cursor;
				cursor = NULL;
			}
			viewCursor = false;
		}
		
		//Отрисовка HUD
		p->drawHUD(window, vmodex, vmodey);
		//отрисовка инвентаря(ставить последним)
		if (isGui)
			inv.draw(vmodex, vmodey, window, &isGui, &a, p);
		window.display();
		if (p->life == false)
		{
			Entity::deleteAllEntities(&entities);

			// пока что просто выход (реализовать окно смерти и перезагрузки)
			window.close();
			return EXIT_SUCCESS;
		}
	}
	return EXIT_SUCCESS;
}

