#include "WeaponBlock.hpp"


WeaponBlock::WeaponBlock(Texture *t, char singnature, BlockType type, WeaponType wtype) : AbstractBlock(t, singnature, type) { this->wtype = wtype; };
WeaponBlock::WeaponBlock(std::string fileName, char singnature, BlockType type, WeaponType wtype) : AbstractBlock(fileName, singnature, type) { this->wtype = wtype; };
WeaponBlock::WeaponBlock(char signature, std::list<AbstractBlock *> & blocks, WeaponType wtype) : AbstractBlock(signature, blocks) { this->wtype = wtype; };
interactionType WeaponBlock::interact() {
	return weaponItemType;
};

WeaponType WeaponBlock::getType() {
	return this->wtype;
}