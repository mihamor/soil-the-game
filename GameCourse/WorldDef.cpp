#include "WorldDef.h"
using namespace sf;

static Vector2f convert(Vector2u vec) {
	return Vector2f(vec.x, vec.y);
}

HudItems HUD::loadHudItems(std::string invBg, std::string playerHud, std::string craftBg) {
	HudItems items;
	Texture * invBgTexture = new Texture();
	invBgTexture->loadFromFile(invBg);
	Texture * playerHudTexture = new Texture();
	playerHudTexture->loadFromFile(playerHud);

	Texture * craftBgTexture = new Texture();
	craftBgTexture->loadFromFile(craftBg);
	items.playerHud.setSize(convert(playerHudTexture->getSize()));
	items.invBg.setSize(convert(invBgTexture->getSize()));
	items.craftBg.setSize(convert(craftBgTexture->getSize()));
	items.invBg.setTexture(invBgTexture);
	items.playerHud.setTexture(playerHudTexture);
	items.craftBg.setTexture(craftBgTexture);
	return items;
}