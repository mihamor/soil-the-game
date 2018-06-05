#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

typedef unsigned int saveSlotNumber;

namespace MENU{
	bool isEmptySlot(unsigned int slot);
}

saveSlotNumber saveMenu(RenderWindow & window, bool mode, int vmodex, int vmodey);