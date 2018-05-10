#pragma once

#include "AbstractBlock.hpp"
#include "Block.hpp"
#include "DoorBlock.h"
#include "TreeBlock.hpp"
#include "Slot.hpp"
#include <vector>
#include "Inventory.hpp"

class Recipe
{

	std::vector<Slot *> required;
	Slot * result;
public:
	Recipe(std::vector<Slot *> rec, Slot * result) {
		this->required = rec;
		this->result = result;
	}
	
	std::vector<Slot *> getRequired() {
		return required;
	}

	bool ifMatchesInv(Inventory & inv) {
		
		for (Slot * reqS : required) {
			bool wasFound = false;
			for (Slot * s : *(inv.getList())) {
				if (s->block->singnature = reqS->block->singnature
					&& s->amount >= reqS->amount) wasFound = true;
			}
			if (!wasFound) return false;
		}
		return true;
	}
	Slot * getResult() {
		return result;
	}


};

