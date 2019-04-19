#include "Entity.hpp"



Entity::Entity()
{
	_observers.clear();
}
AnimationFactory Entity::factory = AnimationFactory();

Entity::Entity(AnimationManager &a, int X, int Y) : Entity()
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