#pragma once
#include <SFML/Graphics.hpp>
#include "Slot.hpp"
#include "Entity.hpp"

using namespace sf;

class Player : public Entity
{
private:
	bool onLadder, shoot;
	enum { stay, walk, duck, jump, climb, swim } STATE;
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

public:
	bool onGround;
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

};

// pattern state
class State {
protected:
	std::string stateName;
public:
	std::string getStateName() {
		return stateName;
	}
	virtual void stay(Player * p)
	{
		//std::cout << "   already ON\n";
	}
	virtual void walkLeft(Player * p)
	{
		//cout << "   already OFF\n";
	}
	virtual void walkRight(Player * p)
	{
		//cout << "   already OFF\n";
	}
	virtual void duck(Player * p)
	{
		//cout << "   already OFF\n";
	}
	virtual void jump(Player * p)
	{
		//cout << "   already OFF\n";
	}
};
class WalkLeftState : State {
public:
	WalkLeftState() {
		stateName = "walkLeft";
	}
	void walkLeft(Player * p);
	void walkRight(Player * p);
	void stay(Player * p);
	void duck(Player * p);
	void jump(Player * p);
};
class WalkRightState : State {
public:
	WalkRightState() {
		stateName = "walkRight";
	}
	void walkLeft(Player * p);
	void walkRight(Player * p);
	void stay(Player * p);
	void duck(Player * p);
	void jump(Player * p);
};
class StayState : State {
public:
	StayState() {
		stateName = "stay";
	}
	void walkLeft(Player * p);
	void walkRight(Player * p);
	void stay(Player * p);
	void duck(Player * p);
	void jump(Player * p);
};
class DuckState : State {
public:
	DuckState() {
		stateName = "duck";
	}
	void walkLeft(Player * p);
	void walkRight(Player * p);
	void stay(Player * p);
	void duck(Player * p);
	void jump(Player * p);
};
class JumpState : State {
public:
	JumpState() {
		stateName = "jump";
	}
	void walkLeft(Player * p);
	void walkRight(Player * p);
	void stay(Player * p);
	void duck(Player * p);
	void jump(Player * p);
};
