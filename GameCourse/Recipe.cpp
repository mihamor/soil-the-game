#include "Recipe.hpp"
#include "AbstractBlock.hpp"
#include "Block.hpp"
#include "DoorBlock.h"
#include "TreeBlock.hpp"

Recipe::Recipe(std::vector<Slot *> rec, Slot * result) {
	this->required = rec;
	this->result = result;
}

std::vector<Slot *> Recipe::getRequired() {
	return required;
}

bool Recipe::ifMatchesInv(Inventory & inv) {

	for (Slot * reqS : required) {
		bool wasFound = false;
		for (Slot * s : *(inv.getList())) {
			if (s->block->singnature == reqS->block->singnature
				&& s->amount >= reqS->amount) wasFound = true;
		}
		if (!wasFound) return false;
	}
	return true;
}
Slot *Recipe::getResult() {
	return result;
}