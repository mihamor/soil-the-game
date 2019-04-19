#include "State.hpp"
#include "PLAYER.hpp"

void setValuesToJump(Player * p) {
	p->setDy(-0.4);
	p->setOnGround(false);
	p->getSoundHandler()->play("player_jump");
	p->getAnimationManager()->set("jump");
}
void setValuesToStay(Player * p) {
	p->setDx(0);
	p->getAnimationManager()->set("stay");
}
void setValuesToDuck(Player * p) {
	p->setDx(0);
	p->getAnimationManager()->set("duck");
}
void setValuesToWalk(Player * p, int dir) {
	p->setDx(dir ? -0.1 : 0.1);
	p->setDir(dir);
	p->getAnimationManager()->set("walk");
}

void WalkRightState::walkLeft(Player * p)
{
	setValuesToWalk(p, 1);
	p->setCurrentState((State *)(new WalkLeftState()));
}
void WalkRightState::walkRight(Player * p)
{
	std::cout << "Already in walkRight state" << std::endl;
}

void WalkRightState::stay(Player * p)
{
	setValuesToStay(p);
	p->setCurrentState((State *)(new StayState()));
}
void WalkRightState::duck(Player * p)
{
	setValuesToDuck(p);
	p->setCurrentState((State *)(new DuckState()));
}
void WalkRightState::jump(Player * p)
{
	setValuesToJump(p);
	p->setCurrentState((State *)(new JumpState()));
}

void WalkLeftState::walkLeft(Player * p)
{
	std::cout << "Already in walkLeft state" << std::endl;
}
void WalkLeftState::walkRight(Player * p)
{
	setValuesToWalk(p, 0);
	p->setCurrentState((State *)(new WalkRightState()));
}

void WalkLeftState::stay(Player * p)
{
	setValuesToStay(p);
	p->setCurrentState((State *)(new StayState()));
}
void WalkLeftState::duck(Player * p)
{
	setValuesToDuck(p);
	p->setCurrentState((State *)(new DuckState()));
}
void WalkLeftState::jump(Player * p)
{
	setValuesToJump(p);
	p->setCurrentState((State *)(new JumpState()));
}
///////////////////////////////////
void StayState::walkLeft(Player * p)
{
	setValuesToWalk(p, 1);
	p->setCurrentState((State *)(new WalkLeftState()));
}
void StayState::walkRight(Player * p)
{
	setValuesToWalk(p, 0);
	p->setCurrentState((State *)(new WalkRightState()));
}
void StayState::stay(Player * p)
{
	std::cout << "Already in stay state" << std::endl;
}
void StayState::duck(Player * p)
{
	setValuesToDuck(p);
	p->setCurrentState((State *)(new DuckState()));
}
void StayState::jump(Player * p)
{
	setValuesToJump(p);
	p->setCurrentState((State *)(new JumpState()));
}
/////////////////////
void DuckState::walkLeft(Player * p)
{
	setValuesToWalk(p, 1);
	p->setCurrentState((State *)(new WalkLeftState()));
}
void DuckState::walkRight(Player * p)
{
	setValuesToWalk(p, 0);
	p->setCurrentState((State *)(new WalkRightState()));
}


void DuckState::stay(Player * p)
{
	setValuesToStay(p);
	p->setCurrentState((State *)(new StayState()));
}
void DuckState::duck(Player * p)
{
	std::cout << "Already in duck state" << std::endl;
}
void DuckState::jump(Player * p)
{
	setValuesToJump(p);
	p->setCurrentState((State *)(new JumpState()));
}
///////////////////////////////
void JumpState::walkLeft(Player * p)
{
	p->setDir(true);
	p->setDx(-0.1);
}
void JumpState::walkRight(Player * p)
{
	p->setDir(false);
	p->setDx(0.1);
}
void JumpState::stay(Player * p)
{
	setValuesToStay(p);
	p->setCurrentState((State *)(new StayState()));
}
void JumpState::duck(Player * p)
{
	setValuesToDuck(p);
	p->setCurrentState((State *)(new DuckState()));
}
void JumpState::jump(Player * p)
{
	std::cout << "Already in jump state" << std::endl;
}