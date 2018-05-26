#include "Slot.hpp"

Slot::Slot(AbstractBlock *pb, int amount)
{
	this->amount = amount;
	block = pb;
}

bool Slot::isStacked()
{
	if (amount < 128 && amount > 0)
		return false;
	return true;
}
