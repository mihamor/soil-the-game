#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

typedef unsigned int saveSlotNumber;

static bool isPointed(IntRect button, RenderWindow & window) {
	return button.contains(Mouse::getPosition(window));
}

saveSlotNumber saveMenu(RenderWindow & window, bool mode)
{
	Vector2u res = window.getSize();
	window.clear();
	bool availableSlots[3];
	for (int i = 0; i < 3; i++) availableSlots[i] = !TMap::isEmptySlot(i+1);

	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("menu/saveslot1.png");

	Vector2u buttonSize = menuTexture1.getSize();
	menuTexture2.loadFromFile("menu/saveslot2.png");
	menuTexture3.loadFromFile("menu/saveslot3.png");
	menuBackground.loadFromFile("menu/menubg.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menuBg(menuBackground);
	bool isMenu = 1;
	saveSlotNumber menuNum;
	menu1.setPosition((res.x - buttonSize.x) / 2, res.y / 2);
	menu2.setPosition((res.x - buttonSize.x) / 2, res.y / 2 + 60);
	menu3.setPosition((res.x - buttonSize.x) / 2, res.y / 2 + 120);
	menuBg.setPosition(0, 0);

	while (isMenu)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				return 0;
			}
			if (event.type == Event::Resized)
			{
			}
			if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left && menuNum != 0)
				if((mode && availableSlots[menuNum-1]) || !mode) isMenu = false;
		}

		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (isPointed(IntRect((res.x - buttonSize.x) / 2, res.y / 2, buttonSize.x, buttonSize.y), window)) { menu1.setColor(availableSlots[0] ? Color::Blue : Color::Red); menuNum = 1; }
		else if (isPointed(IntRect((res.x - buttonSize.x) / 2, res.y / 2 + 60, buttonSize.x, buttonSize.y), window)) { menu2.setColor(availableSlots[1] ? Color::Blue : Color::Red); menuNum = 2; }
		else if (isPointed(IntRect((res.x - buttonSize.x) / 2, res.y / 2 + 120, buttonSize.x, buttonSize.y), window)) { menu3.setColor(availableSlots[2] ? Color::Blue : Color::Red); menuNum = 3; }
		else menuNum = 0;

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
	window.clear();

	return menuNum;
}