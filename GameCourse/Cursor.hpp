#pragma once
#include "anim.hpp"
#include "PLAYER.hpp"
using namespace sf;
class GameCursor
{
	bool viewCursor;
	AnimationManager anim;
	int x, y;
	Vector2i res;
	bool isOkay;
public:
	GameCursor(Vector2i res);
	void update(bool isRange, Vector2i a, float time, Player * p = nullptr);
	void draw(RenderWindow & window);
	bool getStatus() {
		return isOkay;
	}
	~GameCursor();
};

