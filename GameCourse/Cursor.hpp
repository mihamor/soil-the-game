#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;
class Cursor
{
	bool viewCursor;
	Texture * c;
	RectangleShape * cursor;
public:
	Cursor() {
		
		viewCursor = true;
		c = new Texture();
		if (!c->loadFromFile("cursor.png")) {
			abort();
		}
		cursor = new RectangleShape(Vector2f(32, 32));
		cursor->setTexture(c);
	}
	void update(bool isRange, Vector2i a) {
		if (isRange)
		{
			if (!this->viewCursor || !cursor) {
				cursor = new RectangleShape(Vector2f(32, 32));
				cursor->setTexture(c);
			}
			cursor->setPosition(a.x, a.y);
			viewCursor = true;
		}
		else {
			viewCursor = false;
			if(!cursor)delete cursor;
			cursor = 0;

		}
	}

	void draw(RenderWindow & window) {
		if (viewCursor && cursor) window.draw(*cursor);
	}
	~Cursor() {
		if (viewCursor) {
			delete c;
			delete cursor;
		}
	}
};

