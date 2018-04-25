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
	void addSlot(Block * pb);
	void draw(float vmodex, float vmodey, RenderWindow &window, bool *isGui, Vector2i * posMouse, Player * p);
	void saveInventory();
	bool isRectClicked(sf::RectangleShape &rectToClick, sf::RenderWindow &window);
};

