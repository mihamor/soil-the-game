#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Slot.hpp"
#include "PLAYER.hpp"

using namespace sf;
class Inventory
{
private:
	std::list<Slot* > slots;
	int added;
	int maxSlots;

public:
	
	std::list<Slot* > * getList();
	Inventory(int maxSlots);
	void addSlot(AbstractBlock * pb);
	void draw(float vmodex, float vmodey, RenderWindow &window, bool *isGui, Vector2i * posMouse, Player * p);
	void saveInventory();
	bool isRectClicked(sf::RectangleShape &rectToClick, sf::RenderWindow &window);
	bool isRectClickedToDel(sf::RectangleShape &rectToClick, sf::RenderWindow &window);
	void reduceAmount(AbstractBlock & toReduce);
	bool isFull(AbstractBlock * pb);
};

