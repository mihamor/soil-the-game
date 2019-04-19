#pragma once
#include <iostream>

class Player;

class State {
protected:
	std::string stateName;
public:
	std::string getStateName() {
		return stateName;
	}
	virtual void stay(Player * p) = 0;
	virtual void walkLeft(Player * p) = 0;
	virtual void walkRight(Player * p) = 0;
	virtual void duck(Player * p) = 0;
	virtual void jump(Player * p) = 0;
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