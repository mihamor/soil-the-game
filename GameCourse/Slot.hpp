#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Block.hpp"

using namespace sf;

class Slot
{
public:
	AbstractBlock * block;
	int amount;

	Slot(AbstractBlock *pb, int amount);
	bool isStacked();

};

