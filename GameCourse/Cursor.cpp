#include "Cursor.hpp"

GameCursor::GameCursor() {
	viewCursor = true;
	Texture * c = new Texture();
	if (!c->loadFromFile("sprites/cursor.png")) {
		abort();
	}
	anim.loadFromXML("sprites/cursor_anim.xml", c);

	anim.set("in");
	//cursor = new RectangleShape(Vector2f(32, 32));
	//cursor->setTexture(c);
}
void GameCursor::update(bool isRange, Vector2i a, float time) {
	this->x = a.x;
	this->y = a.y;
	if (isRange) anim.set("in");
	else anim.set("out");
	anim.tick(time);
}

void GameCursor::draw(RenderWindow & window) {
	anim.play();
	anim.draw(window, x, y);
};
GameCursor::~GameCursor() {
	delete anim.getTexture();
}