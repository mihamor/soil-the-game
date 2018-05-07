#include "Entity.hpp"


Entity::Entity()
{}

Entity::Entity(AnimationManager &a, int X, int Y)
{
	x = X;
	y = Y;
	anim = a;
	life = true;
	dir = 0;
}

void Entity::draw(RenderWindow &window, float offsetX, float offsetY)
{

	anim.draw(window, x - offsetX, y - offsetY);
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
void Entity::entitiesInteraction(std::list<Entity*>  *entities, Entity * player)
{
	std::list<Entity*>::iterator it;
	for (it = entities->begin(); it != entities->end(); it++)
	{
		if ((*it)->name == "Enemy")
		{
			Entity *e = *it;

			if (!e->life)
			{
				it = entities->erase(it);
				delete e;
			}

			if ((player->getRect().intersects(e->getRect()) && player->dy > 0))
			{
				e->dx = 0;
				e->life = false;
				it = entities->erase(it);
				delete e;

				player->dy = -0.2;
			}
			else if (player->getRect().intersects(e->getRect())) { player->life = false; }

			for (std::list<Entity*>::iterator it2 = entities->begin(); it2 != entities->end(); it2++)
			{
				Entity *b = *it2;
				if (b->name == "Bullet")
				{
					if (b->getRect().intersects(e->getRect()))
					{
						it2 = entities->erase(it2);
						b->life = false;
						it = entities->erase(it);
						e->life = false;
						delete b;
						delete e;
					}

				}
			}
		}
	}
	for (it = entities->begin(); it != entities->end(); it++)
	{
		Entity *b = *it;
		if (b->name == "Bullet")
			if (!b->life) {
				it = entities->erase(it);
				delete b;
			}
	}
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