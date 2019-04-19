#include "Weapon.hpp"

Bullet::Bullet(AnimationManager a, int X, int Y, bool side)
{
	anim = a;
	dir = side;
	x = X;
	y = Y;

	anim.set("move"); 
	name = "Bullet";
	w = anim.getFrameWidth(0, "move") / 2;
	dx = dir ? -0.3 : 0.3;
	h = anim.getFrameHeight(0, "move");

	life = true;
	hit = false;

	damage = 1;

	anim.flip(side);
}
Bullet::~Bullet() {}

void Bullet::update(float time, String TileMap[], std::list<AbstractBlock *> blocks)
{
	
	x += dx * time;
	for (int i = (y) / BLOCK_SIZE; i < (y + h) / BLOCK_SIZE; i++)
		for (int j = (x) / BLOCK_SIZE; j < (x + w) / BLOCK_SIZE; j++)
		{
			char s = TileMap[i][j];
			AbstractBlock * b = AbstractBlock::getBlockFromList(s, blocks);
			if (b->getCollision())
			{
				anim.set("explode"); 
				dx = 0; 
				life = false;

			}
		}

	anim.tick(time);
	
}

Entity * Bullet::clone()
{
	AnimationManager manager = *Entity::factory.getAnimationManager(this->anim.getFileNameOrigin(), (Texture *)this->anim.getTexture());
	return new Bullet(manager, this->x, this->y, this->dir);
}

int Bullet::getDamage()
{
	return this->damage;
}
int Sword::getDamage()
{
	return this->damage;
}




Sword::Sword(AnimationManager a, int X, int Y, bool side)
{
	anim = a;
	dir = side;
	x = X;
	y = Y;

	anim.set("sword");
	w = anim.getFrameWidth(1, "sword");
	h = anim.getFrameHeight(1, "sword");
	dy = 0.05;
	name = "Sword";

	damage = 3;

	life = true;
	hit = false;

	anim.flip(side);
}
Sword::~Sword() {}

void Sword::update(float time, String TileMap[], std::list<AbstractBlock *> blocks)
{

	if (anim.isOver()) this->life = false;
	else y += dy * time;

	anim.tick(time);
}

Entity * Sword::clone()
{
	AnimationManager manager = *Entity::factory.getAnimationManager(this->anim.getFileNameOrigin(), (Texture *)this->anim.getTexture());
	return new Sword(manager, this->x, this->y, this->dir);
}
