#pragma once
#include <SFML/Graphics.hpp>
#include "Slot.hpp"
#include "Entity.hpp"

using namespace sf;

class Player :public Entity
{
private:
	bool onGround, onLadder, shoot;
	enum { stay, walk, duck, jump, climb, swim } STATE;
	int range;
	Slot * hand;


	//hud items
	Text amountShow;
	Font font;

public:
	std::map<std::string, bool> key;
	Player(AnimationManager &a, int X, int Y);
	void setHand(Slot * bl);
	Slot * getHand();
	void reduceAmount(std::list<Slot* >  * slots);
	bool isInRange(int x, int y, double offsetX, double offsetY);
	void KeyCheck();
	bool isMoving();
	void update(float time, String TileMap[], std::list<AbstractBlock *> blocks);
	void Collision(int dir, String TileMap[], std::list<AbstractBlock *> blocks);
	void drawHUD(RenderWindow & window, int vmodex, int vmodey, HudItems & items);
};