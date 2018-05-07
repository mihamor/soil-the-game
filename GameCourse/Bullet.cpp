#include "Bullet.hpp"
#include "Block.hpp"

Bullet::Bullet(AnimationManager a, int X, int Y, bool side)
{
	anim = a;
	dir = side;
	anim.set("move");
	x = X;
	y = Y;
	dx = 0.3;
	if (dir == 1) dx = -0.3;
	w = h = 6;
	life = true;
	name = "Bullet";
}
Bullet::~Bullet() {}

void Bullet::update(float time, String TileMap[], std::list<AbstractBlock *> blocks)
{
	x += dx * time;

	for (int i = (y) / 32; i < (y + h) / 32; i++)
		for (int j = (x) / 32; j < (x + w) / 32; j++)
		{
			//Block b(TileMap, i, j);
			char s = TileMap[i][j];
			AbstractBlock * b = AbstractBlock::getBlockFromList(s, blocks);
			if (b->getCollision())
			{
				anim.set("explode"); dx = 0; life = false;
			}
		}


	anim.tick(time);
}