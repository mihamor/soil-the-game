#pragma once
#include "Inventory.hpp"
class Chest :
	public Inventory
{
public:
	void draw(float vmodex, float vmodey, RenderWindow &window, bool *isGui, Vector2i * posMouse, Inventory *  mainInventory, HudItems & items);
	bool addSlotToList(Slot * slot);
	Chest(int maxSlots);
	~Chest();
};

