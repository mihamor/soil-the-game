#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Block.hpp"

using namespace sf;

class Slot
{
public:
	Block * block;
	int amount;

	Slot(Block *pb, int amount)
	{
		this->amount = amount;
		block = pb;
	}

	bool isStacked()
	{
		if (amount < 128 && amount > 0)
			return false;
		return true;
	}

};

