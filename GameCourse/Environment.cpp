#include "Environment.hpp"
#include "ChestLoader.hpp"

Environment::Environment(int vmodex, int vmodey, int choice, int slot, RenderWindow & window) {
	this->vmodex = vmodex;
	this->vmodey = vmodey;
	this->menuChoice = choice;
	this->slot = slot;
	this->drawFullRender = false;


	initMap();
	if (choice == 1) {
		if (!TMap::loadTileMapFromSlot(slot, TileMap, TileMapBg)) assert(0 && "Invalid slot");
	}
	else {
		WorldManager worldManager;
		Map generatedMap = worldManager.generateWorld((AbstractWorldGenerator* )new DefaultWorldGenerator());

		String * generatedBackground = generatedMap.background;
		String * generatedForeground = generatedMap.foreground;
		TMap::copyFrom(generatedForeground, TileMap);
		TMap::copyFrom(generatedBackground, TileMapBg);
	}

	cursor = new GameCursor(Vector2i(vmodex, vmodey));
	Texture * playerT = new Texture();
	Texture * combatT = new Texture();
	this->hItems = HUD::loadHudItems("menu/invBg.png", "menu/chestBg.png", "menu/playerHud.png", "menu/craftBg.jpg", "menu/heart.jpg");
	//this->hItems.craftBg->loadFromFile("menu/craftBg.png");
	playerT->loadFromFile("sprites/willy.png");
	//playerT->loadFromFile("sprites/megaman.png");
	anim.loadFromXML("sprites/willy_anim.xml", playerT);
	//anim.loadFromXML("sprites/anim_megaman.xml", playerT);

	combatT->loadFromFile("sprites/combatAnim.png");
	//combatAnim.loadFromXML("sprites/combat_anim.xml", combatT);
	combatAnim = (AnimationManager*)Entity::factory.getAnimationManager("./sprites/combat_anim.xml", combatT);

	this->p = new Player(anim, startPlayerPos.x, startPlayerPos.y, &soundSystem);
	inv = new Inventory(INV_SIZE);


	this->entities = new std::list<Entity *>();
	this->entities->push_back(p);

	this->blocks = BlockLoader::loadBlocksFromXml("blocks.xml");
	if (choice == 1) {
		inv->loadInventory(slot, *this->blocks);
		this->chests = ChestLoader::loadChestsFromXml(slot, *this->blocks);
	}

	wbenches["player"] = new Workbench(inv, *blocks, "recipes/player.xml");
	wbenches["workbench"] = new Workbench(inv, *blocks, "recipes/workbench.xml");
	wbenches["furnace"] = new Workbench(inv, *blocks, "recipes/furnace.xml");

	this->ls = new LightHandler(*this->blocks, TileMap, window, vmodey, vmodex);
	this->spawner = new MobSpawner(this->entities);
	this->spawner->generateRandomEntities(W/30);
};

Player * Environment::player() {
	return this->p;
};

std::list<AbstractBlock *> * Environment::blocksList() {
	return this->blocks;
}

std::list<Entity *>  *  Environment::entitiesList() {
	return this->entities;
}

void Environment::addWeapon(WeaponType type) {

	AbstractWeapon * weapon = NULL;


	if (type == Meele)
		weapon = new Sword(*combatAnim, p->x + p->w / 2, p->y + p->h / 4, p->dir);
	else weapon = new Bullet(*combatAnim, p->x + p->w / 2, p->y + p->h / 4, p->dir);
	soundSystem.play(type == Meele ? "sword_use" : "bow_use");

	ContextWeapon * context = new ContextWeapon(weapon);

	entities->push_back((Entity *)context);
}
/*
void Environment::addBullet() {
	this->soundSystem.play("bow_use");
	entities->push_back(new Bullet(combatAnim, p->x + p->w / 2, p->y + p->h / 4, p->dir, Ranged));
}

void Environment::addSword()
{
	this->soundSystem.play("sword_use");
	entities->push_back(new Bullet(combatAnim, p->x + p->w / 2, p->y + p->h / 4, p->dir, Meele));
}*/

void Environment::setGuiInv(bool state) {
	isGuiInv = state;
}

void Environment::setGuiChest(bool state)
{
	isGuiChest = state;
}

void Environment::setGuiWorkbench(bool state, std::string trigger) {
	isGuiWorkbench = state;
	this->wbTrigger = trigger;
}
bool Environment::isWorkbenchGui() {
	return this->isGuiWorkbench;
}
void Environment::setBlock(Vector2i a) {
	Slot * hand = p->getHand();
	AbstractBlock * hblock = nullptr;
	if (hand) hblock = hand->block;
	int posx = (a.x + (int)offsetX) / 32;
	int posy = (a.y + (int)offsetY) / 32;
	//bool inRangePlayer = p->isInRange(a.x, a.y, offsetX, offsetY) && !p->intersects(a, vmodey, vmodex);
	bool inRangePlayer = this->cursor->getStatus();
	bool weaponInHand = false;
	if (hblock && hblock->interact() == weaponItemType) { weaponInHand = inRangePlayer = true; }
	if (!inRangePlayer) return;
	AbstractBlock * bl = AbstractBlock::getBlock(*blocks, TileMap, posy, posx);
	
	bool status = TMap::setBlock(p, a.x, a.y, offsetX, offsetY, *blocks, TileMap, TileMapBg, *inv);

	if (status) {
		soundSystem.play("place_block");
		if (hblock && hblock->interact() == chestType) {
			std::string key = std::to_string(posx) + "," + std::to_string(posy);
			std::cout << key << std::endl;
			this->chests[key] = new Chest(CHEST_SIZE);
		}
		if (hblock && hblock->interact() == spriticType && inRangePlayer) ls->addLight(Vector2i(posx, posy));
		else if (hblock && hblock->getBlockType() == Solid && inRangePlayer) this->ls->addPair(Vector2i(posx, posy));
	}else{
		if (bl->interact() == doorType) {
			if (weaponInHand && !this->cursor->getStatus()) return;
			DoorBlock * db = (DoorBlock *)bl;
			std::cout << "Now type is " << (db->doorUse(posx, posy, this->TileMap) != Solid ? "SOLID" : "BACKGROUND") << std::endl;
			soundSystem.play("door_open");
		}
		else if (bl->interact() == chestType) {
			std::string key = std::to_string(posx) + "," + std::to_string(posy);
			if (!chests.count(key)) chests[key] = new Chest(CHEST_SIZE);
			triggeredChest = chests[key];
			setGuiChest(true);
		}else if (bl->interact() == craftType) {
			soundSystem.play("craft_open");
			WorkbenchBlock * wb = (WorkbenchBlock *)bl;
			std::cout << "Craft opening " << wb->getId() << std::endl;
			setGuiWorkbench(true, wb->getId());
		}else if (hand && hand->block->interact() == weaponItemType) {
			WeaponBlock * w = (WeaponBlock *)hand->block;
			this->addWeapon(w->getType());
			return;
		}
	}
	std::cout << "Interaction " << bl->interact() << std::endl;
	drawFullRender = true;
}
void Environment::removeBlock(Vector2i a) {
	//bool inRangePlayer = p->isInRange(a.x, a.y, offsetX, offsetY) && !p->intersects(a, vmodey, vmodex);
	bool inRangePlayer = this->cursor->getStatus();
	if (!inRangePlayer) return;
	int posx = (a.x + (int)offsetX) / 32;
	int posy = (a.y + (int)offsetY) / 32;
	AbstractBlock * bl = AbstractBlock::getBlock(*blocks, TileMap, posy, posx);
	bool status = TMap::removeBlock(p, a.x, a.y, offsetX, offsetY, *blocks, TileMap, TileMapBg, *inv);
	if (status) {
		soundSystem.play("break_block");
		if (bl->interact() != spriticType) ls->removePair(Vector2i(posx, posy));
		else ls->removeLight(Vector2i(posx, posy));

		if (bl->interact() == chestType) {
			std::string key = std::to_string(posx) + "," + std::to_string(posy);
			if (chests.count(key)) {
				delete this->chests[key];
				chests.erase(key);
			}
		}
	}
	std::cout << "Interaction " << bl->interact() << std::endl;
	if (inRangePlayer && bl->interact() != spriticType)ls->removePair(Vector2i(posx, posy));
	else if (inRangePlayer) ls->removeLight(Vector2i(posx, posy));
	drawFullRender = true;
}
bool Environment::isInvGui() {
	return isGuiInv;
}

bool Environment::isChestGui()
{
	return isGuiChest;
}

bool Environment::isGui() {
	return isGuiInv || isGuiWorkbench || isGuiChest;
}
void Environment::addBlock(Vector2i a) {
	int posx = (a.x + (int)offsetX) / 32;
	int posy = (a.y + (int)offsetY) / 32;
	AbstractBlock * check = AbstractBlock::getBlock(*blocks, TileMap, posy, posx);
	if (check == NULL || check->getSingature() == DEFAULT_BG_SINGNATURE) {
		check = AbstractBlock::getBlock(*blocks, TileMapBg, posy, posx);
		if (check == NULL || check->getSingature() == DEFAULT_BG_SINGNATURE) p->setHand(NULL);
		else inv->addSlot(check);
	}
	else inv->addSlot(check);
}
auto Environment::inventory() {
	return this->inv;
}
bool Environment::isRange(Vector2i a) {
	return p->isInRange(a.x, a.y, offsetX, offsetY);
}

Vector2i Environment::offset() {
	return Vector2i(offsetX, offsetY);
}

void Environment::update(float time, RenderWindow &window, sf::Vector2i a) {
	
	// взаемодействие динамических обьектов
	int killedEnemies = this->entitiesInteraction();
	// апдейт динамических обьектов
	
	if (!isGui()) Environment::updateAllEntities(entities, time, TileMap, *blocks);

	// сдвиг карты при движение 

	if (p->x > vmodex / 2 && p->x  <  W*(32) - vmodex / 2) offsetX = p->x - vmodex / 2;
	if (p->y > vmodey / 2 && p->y < H*(32) - vmodey / 2) offsetY = p->y - vmodey / 2;
	this->cursor->update(isRange(a), a, time,Vector2f(offsetX, offsetY), this->entities);
	// отрисовка общего задника
	// отрисовка блоков

	Environment::drawViewField(blocks, TileMap, TileMapBg, offsetX, offsetY, window, vmodex, vmodey);
	// отрисовка сущностей
	Environment::drawAllEntities(entities, offsetX, offsetY, window);
	// отрисовка курсора

	int t = groundLevel * BLOCK_SIZE + groundLevel * BLOCK_SIZE / 4;

	if (p->y > t) {
		ls->render(offsetX, offsetY, p->x, p->y, window, !drawFullRender);
		if (drawFullRender) drawFullRender = false;
	}

	if (p->isMoving()) drawFullRender = true;
	//Отрисовка HUD
	p->drawHUD(window, vmodex, vmodey, this->hItems);
	//отрисовка инвентаря(ставить последним)
	if (isGuiInv)
		this->inv->draw(vmodex, vmodey, window, &isGuiInv, &a, p, this->hItems);
	else if (isGuiWorkbench)
		this->wbenches[wbTrigger]->draw(window, vmodey, vmodex, &isGuiWorkbench, &this->hItems, this->soundSystem);
	else if (isGuiChest)
		this->triggeredChest->draw(vmodex, vmodey, window, &isGuiChest, &a, inv, this->hItems);

	
	cursor->draw(window);

	//spawner->check(killedEnemies);
}

Environment::~Environment() {
	Environment::deleteAllEntities(entities);
	delete entities;


	inv->saveInventory(this->slot);
	TMap::saveTileMapToSlot(slot, TileMap, TileMapBg);
	ChestLoader::saveChestsToXml(this->chests, slot);

	while (!this->blocks->empty()) {
		auto it = blocks->begin();
		AbstractBlock * b = *it;
		it = blocks->erase(it);
		delete b->getRectangleShape()->getTexture();
		delete b;
		
	}

	delete blocks;
	delete ls;
	delete cursor;
	delete anim.getTexture();
	delete spawner;
	delete wbenches["player"];
	delete wbenches["workbench"];
	delete wbenches["furnace"];
}


void Environment::initMap() {
	for (int y = 0; y < H; y++)
		for (int x = 0; x < W; x++) {
			TileMap[y].insert(0, " ");
			TileMapBg[y].insert(0, " ");
		}
}
void Environment::drawViewField(std::list<AbstractBlock*> * blocks, String * TileMap, String * TileMapBg, double offsetX, double offsetY,  RenderWindow & window, int vmodex, int vmodey)
{
	RectangleShape rectangle;
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
		{
			float posx = (float)(j * 32 - offsetX);
			float posy = (float)(i * 32 - offsetY);
			float reserve = BLOCK_SIZE * 0.9;
			if (posy > vmodey || posx > vmodex || posx < 0 - reserve || posy < 0 - reserve) continue;


			AbstractBlock *b = AbstractBlock::getBlock(*blocks, TileMap, i, j);
			if (b->getBlockType() == Background && b->interact() == removeType) b = AbstractBlock::getBlock(*blocks, TileMapBg, i, j);
			if (b != NULL)
				rectangle = *b->getRectangleShape();
			else
			{
				fprintf(stderr, "Unknown block was found ");
				std::cout << (char)TileMap[i][j] << std::endl;
				abort();
			}
			if (b->interact() == spriticType) {

				//std::cout << posx << " " << posy << std::endl;
				AbstractBlock *bgBlock = AbstractBlock::getBlock(*blocks, TileMapBg, i, j);

				rectangle = *bgBlock->getRectangleShape();
				rectangle.setPosition(posx, posy);

				SpriticBlock * sb = (SpriticBlock*)b;
				Sprite sp = sb->getSprite();
				//sp.setColor(Color::Transparent);
				sp.setPosition(posx, posy);


				window.draw(rectangle);
				window.draw(sp);

			}
			else {
				rectangle.setPosition(posx, posy);
				window.draw(rectangle);
			}
		}
}

void Environment::deleteAllEntities(std::list<Entity*>  *entities)
{
	for (std::list<Entity*>::iterator it = entities->begin(); it != entities->end(); it++)
	{
		Entity * b = *it;
		it = entities->erase(it);
		delete b;
	}
}
int Environment::entitiesInteraction()
{
	std::list<Entity*>::iterator it;
	int counter = 0;
	for (it = entities->begin(); it != entities->end(); it++)
	{
		if ((*it)->name == "Enemy")
		{
			Entity *e = *it;

			if (!e->life)
			{
				counter++;
				it = entities->erase(it);
				e->kill();
			}

			if ((player()->getRect().intersects(e->getRect()) && player()->dy > 0))
			{
				//e->dx = 0;
				soundSystem.play("stab_enemy");
				e->life = e->life - 1;
				if (!e->life) {
					counter++;
					it = entities->erase(it);
					e->kill();
					if (player()->life != 3) {
						player()->life++;
						soundSystem.play("heal_up");
					}
				}

				player()->dy = -0.2;
			}
			else if (player()->getRect().intersects(e->getRect()) && !player()->dy) {
				soundSystem.play("stab_enemy");
				player()->hitted(e->dir);
			}

			for (std::list<Entity*>::iterator it2 = entities->begin(); it2 != entities->end(); it2++)
			{
				Entity *b = *it2;
				if (b->getName() == "Bullet" || b->getName() == "Sword")
				{
					if (b->getRect().intersects(e->getRect()))
					{
						soundSystem.play("stab_enemy");
						bool dirSplash = b->getDir();
						if (b->isAlive()) e->hitted(dirSplash);

						b->setLife(0);
						if (b->getName() == "Bullet") {
							it2 = entities->erase(it2);
							delete b;
						}

						//std::cout << e->hit << std::endl;
						if (!e->life) {
							counter++;
							it = entities->erase(it);
							if (player()->life != 3) {
								player()->life++;
								soundSystem.play("heal_up");
							}
							e->kill();
						}
					}

				}
			}
		}
	}
	for (it = entities->begin(); it != entities->end(); it++)
	{
		Entity *b = *it;
		if (b->getName() == "Bullet") {
			if (!b->isAlive()) {
				it = entities->erase(it);
				delete b;
			}
		}
		if (b->getName() == "Sword") {
			//std::cout << player->dir << std::endl;
			if (player()->dir) { b->setX(player()->x - 50); }
			else { b->setX(player()->getX()); }

			b->flip(player()->getDir());
			b->setY(player()->getY());
			if (b->isOver()) {
				it = entities->erase(it);
				delete b;
			}
		}
	}
	return counter;
}
void Environment::updateAllEntities(std::list<Entity*>  *entities, float time, String * TileMap, std::list<AbstractBlock *> blocks)
{
	for (std::list<Entity*>::iterator it = entities->begin(); it != entities->end(); it++)
	{
		(*it)->update(time, TileMap, blocks);
	}
}
void Environment::drawAllEntities(std::list<Entity*>  *entities, double offsetX, double offsetY, RenderWindow &window)
{
	for (std::list<Entity*>::iterator it = entities->begin(); it != entities->end(); it++)
	{

		(*it)->draw(window, offsetX, offsetY);
	}
}