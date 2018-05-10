#include "PLAYER.hpp"


static String intToStr(int value)
{
	std::string str = std::to_string(value);
	std::locale locale;
	String result(str, locale);
	return result;
}

Player::Player(AnimationManager &a, int X, int Y)
{
	h = a.getFrameHeight(0, "stay");
	w = a.getFrameWidth(0, "stay");
	x = X;
	y = Y;
	anim = a;
	life = 3;
	STATE = stay;
	name = "Player";
	range = 5;
	this->hand = NULL;
	hit = false;
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
		dir = 1;
		if (STATE != duck) dx = -0.1;
		if (STATE == stay) STATE = walk;
	}
	if (key["R"])
	{
		dir = 0;
		if (STATE != duck) dx = 0.1;
		if (STATE == stay) STATE = walk;
	}

	if (key["Up"])
	{
		if (STATE == stay || STATE == walk) { dy = -0.4; STATE = jump; }
		if (STATE == swim || STATE == climb) dy = -0.05;
	}
	if (key["Down"])
	{
		if (STATE == stay) { dx = 0; STATE = duck; }
		if (STATE == swim || STATE == climb) dy = 0.05;
	}
	if (key["Space"])
		shoot = true;

	// otpuskanie klavish
	if (!(key["R"] || key["L"]))
	{
		dx = 0;
		if (STATE == walk) STATE = stay;
	}
	if (!(key["Up"] || key["Down"]))
		if (STATE == swim || STATE == climb) dy = 0;
	if (!key["Down"])
		if (STATE == duck) STATE = stay;
	if (!key["Space"])
		shoot = false;
}


void Player::update(float time, String TileMap[], std::list<AbstractBlock *> blocks)
{

	if(!this->hit)KeyCheck();
	if (STATE == stay) anim.set("stay");
	if (STATE == walk) anim.set("walk");
	if (STATE == jump) anim.set("jump");
	if (STATE == duck) anim.set("duck");
	if (STATE == climb)
	{
		//		anim.set("climb");
		anim.pause();
		if (dy != 0) anim.play();
		if (!onLadder) STATE = stay;
	}
	if (shoot)
	{
		anim.set("shoot");
		if (STATE == walk) anim.set("shootAndWalk");
	}
	anim.flip(dir);

	x += dx * time;
	Collision(0, TileMap, blocks);
	if (!onGround) dy = dy + 0.0005*time;
	y += dy * time;
	onGround = false;
	Collision(1, TileMap, blocks);

	anim.tick(time);
	key["R"] = key["L"] = key["Up"] = key["Down"] = key["Space"] = false;
}

void Player::Collision(int dir, String TileMap[], std::list<AbstractBlock *> blocks)
{
	for (int i = y / 32; i < (y + h) / 32; i++)
		for (int j = x / 32; j < (x + w) / 32; j++)
		{
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
					STATE = stay;

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

void Player::drawHUD(RenderWindow & window, int vmodex, int vmodey)
{
	RectangleShape bg(Vector2f(64, 64));
	bg.setFillColor(Color::White);
	bg.setPosition(64, vmodey - 64);
	window.draw(bg);
	if (hand != NULL)
	{
		RectangleShape inHand = hand->block->rectangle;
		Text  amountShow;   //amount of slot
		Font font;
		if (!font.loadFromFile("fonts/arial.ttf"))
		{
			assert(0);
		}
		String ss = intToStr(hand->amount);
		amountShow.setFont(font);
		amountShow.setString(ss);
		amountShow.setFillColor(Color::Black);
		amountShow.setCharacterSize(32);
		amountShow.setPosition(48 + 32, vmodey - 48);
		inHand.setPosition(48 + 32, vmodey - 48);


		

		window.draw(inHand);
		window.draw(amountShow);
	}
	for (int i = 0; i < this->life; i++) {
			CircleShape heart(10);
			heart.setFillColor(Color::Red);
			heart.setPosition(0 + 30 * i, 0);
			window.draw(heart);
	}
}