#include "Game.h"
#include "saveMenu.hpp"


int main() {

	int vmodex = 600;
	int vmodey = 32 * 12;
	ContextSettings contextSettings;
	contextSettings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(vmodex, vmodey), "Miha game", sf::Style::Default, contextSettings);
	window.setMouseCursorVisible(false);
	while (true) {
		window.clear();
		auto choice = menu(window, vmodex, vmodey);
		if (choice == EXIT) break;
		int slot = saveMenu(window, choice == CONTINUE ? true : false, vmodex, vmodey);
		if (slot == -2) break;
		else if (slot == -1) continue;
		execResult res = game(slot, choice, window, vmodex, vmodey);
		if (res == EXIT_GAME) break;

	}
	return EXIT_SUCCESS;
}