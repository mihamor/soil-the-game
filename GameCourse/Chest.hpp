#pragma once
#include "Inventory.hpp"
class Chest :
	public Inventory
{
public:
	void draw(float vmodex, float vmodey, RenderWindow &window, bool *isGui, Vector2i * posMouse, Inventory *  mainInventory, HudItems & items);
	Chest(int maxSlots);
	~Chest();
};

