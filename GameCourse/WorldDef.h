#pragma once
#include <SFML/Graphics.hpp>

//const int H = 18;
//const int W = 39;
const int H = 120;
const int W = 360;

//const int H = 10;
//const int W = 40;


typedef struct  {
	sf::RectangleShape invBg;
	sf::RectangleShape playerHud;
	sf::RectangleShape craftBg;
} HudItems;
namespace HUD {
	HudItems loadHudItems(std::string invBg, std::string playerHud, std::string craftBg);
}