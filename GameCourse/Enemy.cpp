#include "Enemy.hpp"
#include <iostream>
#include <list>
#include "Windows.h"
#include "Block.hpp"


Enemy::Enemy(AnimationManager a, int X, int Y, bool dir)
{
	anim = a;
	anim.set("walk");
	//anim.animList["walk"].sprite.setColor(Color::Red);
	x = X;
	y = Y;
	dx = 0.05;
	if (dir == 1) { dx = -dx; anim.flip(true); }
	w = anim.getFrameWidth(0, "walk");
	h = anim.getFrameHeight(0, "walk");
	life = true;
	name = "Enemy";
}

Enemy::~Enemy() {}

void Enemy::update(float time, String TileMap[], std::list<AbstractBlock *> blocks)
{
	x += dx * time;
	Collision(0, TileMap, blocks);
	if (!onGround) dy = dy + 0.0005*time;
	y += dy * time;
	onGround = false;
	Collision(1, TileMap, blocks);


	if (life)anim.tick(time);
}

void Enemy::Collision(int num, String TileMap[], std::list<AbstractBlock *> & blocks)
{

	for (int i = (y) / BLOCK_SIZE; i < (y + h) / BLOCK_SIZE; i++)
		for (int j = (x) / BLOCK_SIZE; j < (x + w) / BLOCK_SIZE; j++) {
			//Block  b(TileMap, i, j);
		
			char s = TileMap[i][j];
			AbstractBlock * b = AbstractBlock::getBlockFromList(s, blocks);
			if (b->getCollision()) {
				if (dx > 0 && num == 0) {
					x = j * BLOCK_SIZE - w;
					dx = -dx; ///
					anim.flip(true);
				} else if (dx < 0 && num == 0) {
					x = j * BLOCK_SIZE + BLOCK_SIZE;
					dx = -dx;
					anim.flip(false);
				} if (dy > 0 && num == 1) {
					y = i * BLOCK_SIZE - h;
					dy = 0;
					onGround = true;
					STATE = stay;
				} if (dy < 0 && num == 1) {
					y = i * BLOCK_SIZE + BLOCK_SIZE;
					dy = 0;
				}
			}
		}
}