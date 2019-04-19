#pragma once
#include "AbstractBlock.hpp"
#include "Weapon.hpp"
#include "WorldDef.h"

class WeaponBlock :
	public AbstractBlock
{
	WeaponType wtype;
public:

	interactionType interact();
	WeaponBlock(Texture * t, char singnature, BlockType type, WeaponType wtype);
	WeaponBlock(std::string fileName, char singnature, BlockType type, WeaponType wtype);
	WeaponBlock(char signature, std::list<AbstractBlock*>& blocks, WeaponType wtype);


	WeaponType getType();
};

