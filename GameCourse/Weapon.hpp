#pragma once
#include "AbstractBlock.hpp"
#include "Bullet.hpp"
#include "WorldDef.h"

class Weapon :
	public AbstractBlock
{
	WeaponType wtype;
public:

	interactionType interact();
	Weapon(Texture * t, char singnature, BlockType type, WeaponType wtype);
	Weapon(std::string fileName, char singnature, BlockType type, WeaponType wtype);
	Weapon(char signature, std::list<AbstractBlock*>& blocks, WeaponType wtype);


	WeaponType getType();
};

