#include "Bullet.hpp"

Bullet::Bullet(AnimationManager a, int X, int Y, bool side, WeaponType wtype)
{
	this->wtype = wtype;

	anim = a;
	dir = side;
	x = X;
	y = Y;

	if (wtype == Ranged) {
		anim.set("move"); 
		name = "Bullet";
		w = anim.getFrameWidth(0, "move") / 2;
		dx = 0.3;
		h = anim.getFrameHeight(0, "move");
	} else {
		anim.set("sword");
		w = anim.getFrameWidth(1, "sword");
		h = anim.getFrameHeight(1, "sword");
		dy = 0.05;
		name = "Sword";
	}
	
	if (dir) {
		dx = -dx;
	}
	life = true;
	hit = false;

	anim.flip(side);
}
Bullet::~Bullet() {}

void Bullet::update(float time, String TileMap[], std::list<AbstractBlock *> blocks)
{
	
	if (wtype == Meele && anim.isOver()) this->life = false;
	if(wtype == Ranged) x += dx * time;
	else y += dy * time;

	for (int i = (y) / 32; i < (y + h) / 32; i++)
		for (int j = (x) / 32; j < (x + w) / 32; j++)
		{
			//Block b(TileMap, i, j);
			char s = TileMap[i][j];
			AbstractBlock * b = AbstractBlock::getBlockFromList(s, blocks);
			if (b->getCollision())
			{
				if (wtype == Ranged) { anim.set("explode"); dx = 0; life = false; }
			}
		}


	anim.tick(time);
	
}

Entity * Bullet::clone()
{
	AnimationManager manager = *Entity::factory.getAnimationManager(this->anim.getFileNameOrigin(), (Texture *)this->anim.getTexture());
	return new Bullet(manager, this->x, this->y, this->dir, this->wtype);
}
