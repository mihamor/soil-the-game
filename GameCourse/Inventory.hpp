#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Slot.hpp"
#include "PLAYER.hpp"

using namespace sf;
class Inventory
{
protected:
	std::list<Slot* > slots;
	int added;
	int maxSlots;

	Text  amountShow;
	Font font;
public:
	
	std::list<Slot* > * getList();
	Inventory(int maxSlots);
	bool addSlot(AbstractBlock * pb);
	void draw(float vmodex, float vmodey, RenderWindow &window, bool *isGui, Vector2i * posMouse, Player * p, HudItems & items);
	void saveInventory(int slot);
	bool loadInventory(int slot, std::list <AbstractBlock *> &blocks);
	bool isRectClicked(sf::RectangleShape &rectToClick, sf::RenderWindow &window);
	bool isRectClickedToDel(sf::RectangleShape &rectToClick, sf::RenderWindow &window);
	bool reduceAmount(AbstractBlock & toReduce);
	void reduceAmount(Player * p);
	bool isFull(AbstractBlock * pb);
};

