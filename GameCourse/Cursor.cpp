#include "Cursor.hpp"

GameCursor::GameCursor(Vector2i res) {
	viewCursor = true;
	this->isOkay = true;
	Texture * c = new Texture();
	if (!c->loadFromFile("sprites/cursor.png")) {
		abort();
	}
	anim.loadFromXML("sprites/cursor_anim.xml", c);

	anim.set("in");
	this->res = res;
	//cursor = new RectangleShape(Vector2f(32, 32));
	//cursor->setTexture(c);
}
void GameCursor::update(bool isRange, Vector2i a, float time, Vector2f offset,  Player * p) {
	this->x = a.x;
	this->y = a.y;

	
	if (p != nullptr && p->intersects(a, offset.x, offset.y)) isRange = false;

	if (isRange) { anim.set("in");  this->isOkay = true; }
	else {
		anim.set("out");
		this->isOkay = false;
	}
	anim.tick(time);
}

void GameCursor::draw(RenderWindow & window) {
	anim.play();
	anim.draw(window, x, y);
};
GameCursor::~GameCursor() {
	delete anim.getTexture();
}