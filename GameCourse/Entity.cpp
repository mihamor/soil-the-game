#include "Entity.hpp"


Entity::Entity()
{}

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
bool Entity::intersects(Vector2i coords) {
	auto rect = this->anim.getRect();
	return rect.contains(coords);
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
				if (b->name == "Bullet" || b->name == "Sword")
				{
					if (b->getRect().intersects(e->getRect()))
					{
						soundSystem->play("stab_enemy");
						bool dirSplash = b->dir;
						if (b->name == "Bullet") {
							it2 = entities->erase(it2);
							b->life = 0;
							delete b;
						}
						e->hitted(dirSplash);
						//std::cout << e->hit << std::endl;
						if (!e->life) { 
							counter++;
							it = entities->erase(it);
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
		if (b->name == "Bullet") {
			if (!b->life) {
				it = entities->erase(it);
				delete b;
			}
		}
		if (b->name == "Sword") {
			//std::cout << player->dir << std::endl;
			if (player->dir) { b->x = player->x - 50; }
			else { b->x = player->x; }

			b->flip(player->dir);
			b->y = player->y;
			if (!b->life) {
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