#pragma once
#include "menu.hpp"

enum execResult {
	EXIT_GAME = 0,
	TO_MENU
};

execResult game(int slot, MenuChoiceCustom menuChoice, RenderWindow & window,  int vmodex, int vmodey);