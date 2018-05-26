#pragma once
#include "Slot.hpp"
#include <vector>
#include "Inventory.hpp"

class Recipe
{

	std::vector<Slot *> required;
	Slot * result;
public:
	Recipe(std::vector<Slot *> rec, Slot * result);
	std::vector<Slot *> getRequired();
	bool ifMatchesInv(Inventory & inv);
	Slot * getResult();


};

