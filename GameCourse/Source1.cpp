#include <SFML/Graphics.hpp>
#include <iostream>
#include "Windows.h"
#include <Math.h>
#include "tilemap.h"
#include <assert.h>
#include "Environment.hpp"
#include "Cursor.hpp"
#include "menu.hpp"
#include "saveMenu.hpp"
#define SFML_DYNAMIC

#pragma comment(lib, "sfml-graphics-s-d.lib")

using namespace sf;

void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
}
//const int ground = 32 * 18;

int vmodex = 600;
int vmodey = 32 * 12;

int main() {

	ContextSettings contextSettings;
	contextSettings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(vmodex, vmodey), "Miha game", sf::Style::Default, contextSettings);
	window.setMouseCursorVisible(false);
	MenuChoiceCustom menuChoice = menu(window, vmodex, vmodey);
	if (menuChoice == NONE || menuChoice == EXIT) return EXIT_SUCCESS;
	int slot = saveMenu(window, menuChoice == CONTINUE ? true : false, vmodex, vmodey);
	window.clear();
	bool gameOver = false;
	bool Resized = false;

	Clock clock;
	View view;

	Environment e(vmodex, vmodey, menuChoice, slot, window);

	RectangleShape rectangle;
	sf::Vector2i a(0, 0);
	
	while (window.isOpen() && e.player()->life) {
		
		float time = clock.getElapsedTime().asMicroseconds(); // тик рейт
		clock.restart();
		time = time / 400; // делитель ~  задержка милисекунды	
		Vector2i mpos_i = Mouse::getPosition(window);
		Vector2f mpos_f = window.mapPixelToCoords(mpos_i);
		a = Vector2i(mpos_f.x, mpos_f.y);
		// контроль нажатия клавиш
		if (!e.isGui()) {
			if (Keyboard::isKeyPressed(Keyboard::A))
				e.player()->key["L"] = true;
			if (Keyboard::isKeyPressed(Keyboard::D))
				e.player()->key["R"] = true;
			if (Keyboard::isKeyPressed(Keyboard::W))
				e.player()->key["Up"] = true;
			if (Keyboard::isKeyPressed(Keyboard::S))
				e.player()->key["Down"] = true;
			if (Keyboard::isKeyPressed(Keyboard::Space))
				e.player()->key["Space"] = true;
			if (Keyboard::isKeyPressed(Keyboard::E) && a.x <= vmodex && a.y <= vmodey) // взять блок
			{
				e.addBlock(a);
			}
		}
		// call inventory
		if (Keyboard::isKeyPressed(Keyboard::I))
			e.setGuiInv(true);
		if (Keyboard::isKeyPressed(Keyboard::C))
			e.setGuiWorkbench(true, "player");


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				auto list = e.blocksList();
				BlockLoader::saveBlocksToXml(*list);
				window.close();
				return EXIT_SUCCESS;
			}
			if (event.type == Event::Resized)
			{
				//vmodex = event.size.width;
				//vmodey = event.size.height;
				//window.create(sf::VideoMode(vmodex, vmodey, 32), "SFML Window");
			}
			if (event.type == Event::KeyPressed && !e.isGui())
				switch (event.key.code)
				{
				case Keyboard::Space: {
					//e.addSword();
					break;
				}
				default:
					break;
				}
			if(event.type == Event::MouseButtonPressed && !e.isGui())
				switch (event.key.code)
				{
				case Mouse::Right: { // place block
					e.setBlock(a);
					break;
				}
				case Mouse::Left: { // remove block
					e.removeBlock(a);
					break;
				}
				default:
					break;
				}
		}

		e.update(time, window, a);

		window.display();
		if (e.player()->life == false || menuChoice == EXIT)
		{

			// пока что просто выход (реализовать окно смерти и перезагрузки)
			auto list = e.blocksList();
			BlockLoader::saveBlocksToXml(*list);
			window.close();
			return EXIT_SUCCESS;
		}
	}
	return EXIT_SUCCESS;
}

