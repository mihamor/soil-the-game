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
	bool intersects(Vector2i coords, float offsetX, float offsetY) {
		
		int posPx = (this->x +  this->w/2) / 32;
		int posPy = (this->y +  this->h/2) / 32;


		int posx = (coords.x + (int)offsetX) / 32;
		int posy = (coords.y + (int)offsetY) / 32;


		//std::cout << "(" << posPx << ", " << posPy << ")" << " - " << "(" << posx << ", " << posy << ")" << std::endl;

		return posPx == posx && posPy == posy;
	}
	void update(float time, String TileMap[], std::list<AbstractBlock *> blocks);
	void Collision(int dir, String TileMap[], std::list<AbstractBlock *> blocks);
	void drawHUD(RenderWindow & window, int vmodex, int vmodey, HudItems & items);
	
};