#pragma once
#include <SFML/Graphics.hpp>
#include "Slot.hpp"
#include "Entity.hpp"
#include "State.hpp"

using namespace sf;

class Player : public Entity
{
private:
	int range;
	Slot * hand;
	class State * current;

	//hud items
	Text amountShow;
	Font font;
	void playerPosNormalize();

	void walkLeftPlayer();
	void walkRightPlayer();
	void jumpPlayer();
	void stayPlayer();
	void duckPlayer();
	bool onGround;


public:
	
	void setCurrentState(State * state);
	std::string getCurrentStateName();
	std::map<std::string, bool> key;
	Player(AnimationManager &a, int X, int Y, SoundSystem * soundSystem);
	void setHand(Slot * bl);
	Slot * getHand();
	void reduceAmount(std::list<Slot* >  * slots);
	bool isInRange(int x, int y, double offsetX, double offsetY);
	void KeyCheck();
	bool isMoving();
	void update(float time, String TileMap[], std::list<AbstractBlock *> blocks);
	Entity * clone();
	void Collision(int dir, String TileMap[], std::list<AbstractBlock *> blocks);
	void drawHUD(RenderWindow & window, int vmodex, int vmodey, HudItems & items);


	bool isOnGround() { return onGround; }
	void setOnGround(bool value) { onGround = value; }
};
