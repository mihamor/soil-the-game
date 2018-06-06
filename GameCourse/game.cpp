#include "Game.h"
#include <Math.h>
#include <assert.h>
#include "Environment.hpp"


#pragma comment(lib, "sfml-graphics-s-d.lib")

using namespace sf;

//const int ground = 32 * 18;

execResult game(int slot, MenuChoiceCustom menuChoice, RenderWindow & window, int vmodex, int vmodey) {
	
	
	
	if (menuChoice == NONE || menuChoice == EXIT) return EXIT_GAME;
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
		//if (Keyboard::isKeyPressed(Keyboard::I))
		//	e.setGuiInv(true);


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				auto list = e.blocksList();
				BlockLoader::saveBlocksToXml(*list);
				window.close();
				return EXIT_GAME;
			}
			if (event.type == Event::Resized)
			{
				//vmodex = event.size.width;
				//vmodey = event.size.height;
				//window.create(sf::VideoMode(vmodex, vmodey, 32), "SFML Window");
			}
			if (event.type == Event::KeyPressed)
				switch (event.key.code)
				{
				case Keyboard::C: {
					if(!e.isInvGui()) e.setGuiWorkbench(!e.isWorkbenchGui(), "player");
					//e.addSword();
					std::cout << e.isWorkbenchGui() << std::endl;
					break;
				}
				case Keyboard::I: {
					if(!e.isWorkbenchGui()) e.setGuiInv(!e.isInvGui());
					//std::cout << e.isInvGui() << std::endl;
					break;
				}
				case Keyboard::Escape: {
					//...
					return TO_MENU;
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
			return TO_MENU;
		}
	}
	return EXIT_GAME;
}

