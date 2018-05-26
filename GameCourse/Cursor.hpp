#pragma once
#include "anim.hpp"
using namespace sf;
class GameCursor
{
	bool viewCursor;
	AnimationManager anim;
	int x, y;
public:
	GameCursor();
	void update(bool isRange, Vector2i a, float time);
	void draw(RenderWindow & window);
	~GameCursor();
};

