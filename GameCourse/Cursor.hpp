#pragma once
#include <SFML\Graphics.hpp>
#include "anim.hpp"
using namespace sf;
class Cursor
{
	bool viewCursor;
	//Texture * c;
	//RectangleShape * cursor;
	AnimationManager anim;
	int x, y;
public:
	Cursor() {		
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
	void update(bool isRange, Vector2i a, float time) {
		this->x = a.x;
		this->y = a.y;
		if (isRange) anim.set("in");
		else anim.set("out");
		anim.tick(time);
	}

	void draw(RenderWindow & window) {
		anim.play();
		anim.draw(window, x, y);
	};
	~Cursor() {
		delete anim.getTexture();
	}
};

