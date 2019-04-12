#include "Entity.hpp"



Entity::Entity()
{}
AnimationFactory Entity::factory = AnimationFactory();

Entity::Entity(AnimationManager &a, int X, int Y)
{
	x = X;
	y = Y;
	anim = a;
	life = 6;
	dir = 0;
	hit = false;
}

void Entity::hitted(bool dir) {
	bool dirSplash = dir;
	this->dy = -0.2;
	if (dirSplash) this->dx = -0.2;
	else  this->dx = 0.2;
	this->hit = true;
	this->life = this->life - 1;
}

void Entity::draw(RenderWindow &window, float offsetX, float offsetY)
{

	anim.draw(window, x - offsetX, y - offsetY);
}
bool Entity::intersects(Vector2i coords, float offsetX, float offsetY)
{

	int posPx = (this->x + this->w / 2) / 32;
	int posPy = (this->y + this->h / 2) / 32;

	int posx = (coords.x + (int)offsetX) / 32;
	int posy = (coords.y + (int)offsetY) / 32;
	//std::cout << "(" << posPx << ", " << posPy << ")" << " - " << "(" << posx << ", " << posy << ")" << std::endl;
	return posPx == posx && posPy == posy;
}
FloatRect Entity::getRect()
{
	return FloatRect(x, y, w, h);
}
void Entity::deleteAllEntities(std::list<Entity*>  *entities)
{
	for (std::list<Entity*>::iterator it = entities->begin(); it != entities->end(); it++)
	{
		Entity * b = *it;
		it = entities->erase(it);
		delete b;
	}
}
int Entity::entitiesInteraction(std::list<Entity*>  *entities, Entity * player,  SoundSystem * soundSystem)
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
				delete e;
			}

			if ((player->getRect().intersects(e->getRect()) && player->dy > 0))
			{
				//e->dx = 0;
				soundSystem->play("stab_enemy");
				e->life = e->life - 1;
				if (!e->life) {
					counter++;
					it = entities->erase(it);
					delete e;
					if (player->life != 3) {
						player->life++;
						soundSystem->play("heal_up");
					}
				}

				player->dy = -0.2;
			}
			else if (player->getRect().intersects(e->getRect())  && !player->dy) {
				soundSystem->play("stab_enemy");
				player->hitted(e->dir);
			}

			for (std::list<Entity*>::iterator it2 = entities->begin(); it2 != entities->end(); it2++)
			{
				Entity *b = *it2;
				if (b->getName() == "Bullet" || b->getName() == "Sword")
				{
					if (b->getRect().intersects(e->getRect()))
					{
						soundSystem->play("stab_enemy");
						bool dirSplash = b->getDir();
						if(b->isAlive()) e->hitted(dirSplash);

						b->setLife(0);
						if (b->getName() == "Bullet") {
							it2 = entities->erase(it2);
							delete b;
						}
						
						//std::cout << e->hit << std::endl;
						if (!e->life) { 
							counter++;
							it = entities->erase(it);
							if (player->life != 3) {
								player->life++;
								soundSystem->play("heal_up");
							}
							delete e;
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
			if (player->dir) { b->setX(player->x - 50); }
			else { b->setX(player->x); }

			b->flip(player->dir);
			b->setY(player->y);
			if (b->isOver()) {
				it = entities->erase(it);
				delete b;
			}
		}
	}
	return counter;
}
void Entity::updateAllEntities(std::list<Entity*>  *entities, float time, String * TileMap, std::list<AbstractBlock *> blocks)
{
	for (std::list<Entity*>::iterator it = entities->begin(); it != entities->end(); it++)
	{
		(*it)->update(time, TileMap, blocks);
	}
}
void Entity::drawAllEntities(std::list<Entity*>  *entities, double offsetX, double offsetY, RenderWindow &window)
{
	for (std::list<Entity*>::iterator it = entities->begin(); it != entities->end(); it++)
	{

		(*it)->draw(window, offsetX, offsetY);
	}
}