#include "PLAYER.hpp"


static String intToStr(int value)
{
	std::string str = std::to_string(value);
	std::locale locale;
	String result(str, locale);
	return result;
}

void Player::setCurrentState(State * state)
{
	current = state;
}

std::string Player::getCurrentStateName()
{
	return current->getStateName();
}

Player::Player(AnimationManager &a, int X, int Y, SoundSystem * soundSystem)
{
	h = a.getFrameHeight(0, "stay");
	w = a.getFrameWidth(0, "stay");
	x = X;
	y = Y;
	anim = a;
	life = 3;
	//STATE = stay;
	setCurrentState((State* )(new StayState()));
	name = "Player";
	range = 5;
	this->hand = NULL;
	hit = false;


	this->soundHandler = soundSystem;

	// @implement normal hud items connections

	if (!this->font.loadFromFile("fonts/arial.ttf")) assert(0 && "font not loaded");
	amountShow.setFont(font);
	amountShow.setFillColor(Color::White);
	amountShow.setCharacterSize(16);
}

bool Player::isMoving() {
	return dx || dy;
}
void Player::setHand(Slot * bl) { hand = bl; }
Slot * Player::getHand() { return hand; }
void Player::reduceAmount(std::list<Slot* >  * slots)
{
	if (hand == NULL) return;
	for (std::list<Slot* >::iterator it = slots->begin(); it != slots->end(); it++)
	{
		Slot * s = *(it);
		if (AbstractBlock::compare(s->block, hand->block))
		{
			if (--hand->amount == 0)
			{
				it = slots->erase(it);
				hand = NULL;
				return;
			}
			else return;
		}
	}
	return;
}

bool Player::isInRange(int x, int y, double offsetX, double offsetY)
{
	return (abs(this->x - x - offsetX) / 32 < range && abs(this->y - y - offsetY) / 32 < range);
}

void Player::KeyCheck()
{


	if (key["L"])
	{
		walkLeftPlayer();
		//dir = 1;
		//if (STATE != duck) dx = -0.1;
		//if (STATE == stay) STATE = walk;
	}
	if (key["R"])
	{	
		walkRightPlayer();
		//dir = 0;
		//if (STATE != duck) dx = 0.1;
		//if (STATE == stay) STATE = walk;
	}

	if (key["Up"])
	{
		jumpPlayer();
		//if (STATE == stay || STATE == walk) { dy = -0.4; STATE = jump; this->soundHandler->play("player_jump");  }
		//if (STATE == swim || STATE == climb) dy = -0.05;
	}
	if (key["Down"])
	{
		duckPlayer();
		//if (STATE == stay) { dx = 0; STATE = duck; }
		//if (STATE == swim || STATE == climb) dy = 0.05;
	}
	//if (key["Space"])
	//	shoot = true;

	// otpuskanie klavish
	if (!key["R"] && !key["L"] && !key["Down"] && !key["Up"])
	{
		if(getCurrentStateName() != "jump") stayPlayer();
		//dx = 0;
		//if (STATE == walk) STATE = stay;
	}
	if (!key["Space"])
		shoot = false;
}




void Player::update(float time, String TileMap[], std::list<AbstractBlock *> blocks)
{

	if(!this->hit)KeyCheck();
	//if (STATE == stay) anim.set("stay");
	//if (STATE == walk) anim.set("walk");
	//if (STATE == jump) {
	//	anim.set("jump");
	//}
	//if (STATE == duck) anim.set("duck");
	//if (STATE == climb)
	//{
		//		anim.set("climb");
	//	anim.pause();
	//	if (dy != 0) anim.play();
	//	if (!onLadder) STATE = stay;
	//}
	if (shoot)
	{
		anim.set("shoot");
		//if (STATE == walk) anim.set("shootAndWalk");
	}
	anim.flip(dir);

	//std::cout << "dx: " << dx << std::endl;
	float encrease = dx * time;
	int encLimit = 32;
	if (fabs(encrease) > encLimit) { encrease = encrease > 0 ? encLimit : -encLimit; std::cout << "Enc Limit hit!" << std::endl; }
	x += encrease;
	Collision(0, TileMap, blocks);
	if (!onGround) dy = dy + 0.0005*time;
	encrease = dy * time;
	if (fabs(encrease) > encLimit) { encrease = encrease > 0 ? encLimit : -encLimit; std::cout << "Enc Limit hit!" << std::endl; }
	y += encrease;
	onGround = false;
	Collision(1, TileMap, blocks);


	if (x > W * 32 || x < 0 || y < 0 || y > H * 32) playerPosNormalize();

	anim.tick(time);
	key["R"] = key["L"] = key["Up"] = key["Down"] = key["Space"] = false;
}
Entity * Player::clone()
{
	AnimationManager manager = *Entity::factory.getAnimationManager(this->anim.getFileNameOrigin(), (Texture *)this->anim.getTexture());
	return new Player(manager, this->x, this->y, this->soundHandler);
}
void Player::playerPosNormalize() {
	this->x = W * 16;
	this->y = 60;
}

void Player::walkLeftPlayer()
{
	if (current->getStateName() != "walkLeft") {
		std::cout << "walkLeft" << std::endl;
		current->walkLeft(this);
	}
}

void Player::walkRightPlayer()
{
	if (current->getStateName() != "walkRight") {
		std::cout << "walkRight" << std::endl;
		current->walkRight(this);
	}
}

void Player::jumpPlayer()
{
	if (current->getStateName() != "jump") {
		std::cout << "jump" << std::endl;
		current->jump(this);
	}
}

void Player::stayPlayer()
{
	if (current->getStateName() != "stay") {
		std::cout << "stay" << std::endl;
		current->stay(this);
	}
}

void Player::duckPlayer()
{
	if (current->getStateName() != "duck") {
		std::cout << "duck" << std::endl;
		current->duck(this);
	}
}

void Player::Collision(int dir, String TileMap[], std::list<AbstractBlock *> blocks)
{
	for (int i = y / 32; i < (y + h) / 32; i++)
		for (int j = x / 32; j < (x + w) / 32; j++)
		{
			if (i >= H || j >= W || i < 0 || j < 0) continue;
			char s = TileMap[i][j];
			AbstractBlock * b = AbstractBlock::getBlockFromList(s, blocks);
			if (b && b->getCollision())
			{
				if (dx > 0 && dir == 0) x = j * 32 - w;
				else if (dx < 0 && dir == 0) x = j * 32 + 32;
				if (dy > 0 && dir == 1)
				{
					y = i * 32 - h;
					dy = 0;
					onGround = true;

					if(getCurrentStateName() == "jump") stayPlayer();

					if (hit) {
						hit = false;
						dx = 0;
					}
				}
				else if (dy < 0 && dir == 1)
				{
					y = i * 32 + 32;
					dy = 0;
					if (hit) {
						hit = false;
						dx = 0;
					}
				}
			}
		}
}

void Player::drawHUD(RenderWindow & window, int vmodex, int vmodey, HudItems & items)
{
	RectangleShape bg = items.playerHud;
	//bg.setFillColor(Color::White);
	bg.setPosition(64, vmodey - 64);
	window.draw(bg);
	
	
	for (int i = 0; i < this->life; i++) {
			//CircleShape heart(10);
			Sprite heart = items.heart;
			//heart.setFillColor(Color::Red);
			heart.setPosition(0 + 30 * i, 0);
			window.draw(heart);
	}
	if (!hand || !hand->block) return;
	else if (this->getHand()->amount == 0) this->setHand(nullptr);
	else {
		RectangleShape inHand = hand->block->rectangle;
		String ss = intToStr(hand->amount);
		amountShow.setString(ss);
		amountShow.setPosition(48 + 32, vmodey - 48);
		inHand.setPosition(48 + 32, vmodey - 48);
		window.draw(inHand);
		window.draw(amountShow);
	}
}


void setValuesToJump(Player * p) {
	p->dy = -0.4;
	p->onGround = false;
	p->soundHandler->play("player_jump");
	p->anim.set("jump");
}
void setValuesToStay(Player * p) {
	p->dx = 0;
	p->anim.set("stay");
}
void setValuesToDuck(Player * p) {
	p->dx = 0;
	p->anim.set("duck");
}
void setValuesToWalk(Player * p, int dir) {
	p->dx = dir ? -0.1 : 0.1;
	p->dir = dir;
	p->anim.set("walk");
}

void WalkRightState::walkLeft(Player * p)
{
	setValuesToWalk(p, 1);
	p->setCurrentState((State *)(new WalkLeftState()));
	//p->dx = p->dir ? -0.1 : 0.1;
	//p->anim.set("walk");
	//set values
}
void WalkRightState::walkRight(Player * p)
{
	std::cout << "Already in walkRight state" << std::endl;
	
	//p->dx = p->dir ? -0.1 : 0.1;
	//p->anim.set("walk");
	//set values
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
///////////////////////////////////


void WalkLeftState::walkLeft(Player * p)
{
	std::cout << "Already in walkLeft state" << std::endl;
	//p->dx = p->dir ? -0.1 : 0.1;
	//p->anim.set("walk");
	//set values
}
void WalkLeftState::walkRight(Player * p)
{
	setValuesToWalk(p, 0);
	p->setCurrentState((State *)(new WalkRightState()));
	//p->dx = p->dir ? -0.1 : 0.1;
	//p->anim.set("walk");
	//set values
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
	//p->dx = 0;
	//p->anim.set("stay");
	//set values
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
	//p->dx = 0;
	//p->anim.set("duck");
	// set values
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
	p->dir = 1;
	p->dx = -0.1;
	//p->setCurrentState((State *)(new WalkLeftState()));
}
void JumpState::walkRight(Player * p)
{
	p->dir = 0;
	p->dx = 0.1;
	//p->setCurrentState((State *)(new WalkLeftState()));
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
	//p->dy = -0.4;
	//p->onGround = false;
	//p->soundHandler->play("player_jump");
	//p->anim.set("jump");
	//set value
}