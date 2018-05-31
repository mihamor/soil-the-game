#include "Weapon.hpp"


Weapon::Weapon(Texture *t, char singnature, BlockType type, WeaponType wtype) : AbstractBlock(t, singnature, type) { this->wtype = wtype; };
Weapon::Weapon(std::string fileName, char singnature, BlockType type, WeaponType wtype) : AbstractBlock(fileName, singnature, type) { this->wtype = wtype; };
Weapon::Weapon(char signature, std::list<AbstractBlock *> & blocks, WeaponType wtype) : AbstractBlock(signature, blocks) { this->wtype = wtype; };
interactionType Weapon::interact() {
	return weaponItemType;
};

WeaponType Weapon::getType() {
	return this->wtype;
}