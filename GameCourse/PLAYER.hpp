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
	void playerPosNormalize();
public:
	std::map<std::string, bool> key;
	Player(AnimationManager &a, int X, int Y, SoundSystem * soundSystem);
	void setHand(Slot * bl);
	Slot * getHand();
	void reduceAmount(std::list<Slot* >  * slots);
	bool isInRange(int x, int y, double offsetX, double offsetY);
	void KeyCheck();
	bool isMoving();
	bool intersects(Vector2i coords, int vmodey, int vmodex) {
		auto rect = this->anim.getRect();
		
		rect.width = 32;
		rect.height = 32;
		rect.left = vmodex / 2 - 16;
		rect.top = vmodey / 2 - 16;
		return rect.contains(coords);
	}
	void update(float time, String TileMap[], std::list<AbstractBlock *> blocks);
	void Collision(int dir, String TileMap[], std::list<AbstractBlock *> blocks);
	void drawHUD(RenderWindow & window, int vmodex, int vmodey, HudItems & items);
	
};