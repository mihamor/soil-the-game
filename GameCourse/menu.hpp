#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

enum MenuChoiceCustom {
	EXIT,
	CONTINUE,
	NEWGAME,
	NONE
};

MenuChoiceCustom menu(RenderWindow & window, int vmodex, int vmodey);