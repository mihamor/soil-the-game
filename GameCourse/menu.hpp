#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Windows.h"

using namespace sf;

enum MenuChoiceCustom {
	EXIT,
	CONTINUE,
	NEWGAME,
	NONE
};

MenuChoiceCustom menu(RenderWindow & window)
{
	Vector2u res = window.getSize();
	
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("menu/continue.png");
	
	Vector2u buttonSize = menuTexture1.getSize();
	menuTexture2.loadFromFile("menu/newgame.png");
	menuTexture3.loadFromFile("menu/exit.png");
	//aboutTexture.loadFromFile("images/about.png");
	menuBackground.loadFromFile("menu/menubg.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), /*about(aboutTexture),*/ menuBg(menuBackground);
	bool isMenu = 1;
	MenuChoiceCustom menuNum;
	menu1.setPosition( (res.x - buttonSize.x)  / 2, res.y / 2 );
	menu2.setPosition( (res.x - buttonSize.x) / 2, res.y / 2 + 60);
	menu3.setPosition( (res.x - buttonSize.x) / 2, res.y / 2 + 120);
	menuBg.setPosition(0,0);

	//////////////////////////////лемч///////////////////
	while (isMenu)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				return NONE;
			}
			if (event.type == Event::Resized)
			{
				//vmodex = event.size.width;
				//vmodey = event.size.height;
				//window.create(sf::VideoMode(vmodex, vmodey, 32), "SFML Window");
			}
		}

		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = NONE;
		window.clear(Color(129, 181, 221));

		if (IntRect((res.x - buttonSize.x) / 2, res.y / 2, buttonSize.x, buttonSize.y).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = CONTINUE; }
		else if (IntRect((res.x - buttonSize.x) / 2, res.y / 2 + 60, buttonSize.x, buttonSize.y).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = NEWGAME; }
		else if (IntRect((res.x - buttonSize.x) / 2, res.y / 2 + 120, buttonSize.x, buttonSize.y).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = EXIT; }
		else menuNum = NONE;
		if (Mouse::isButtonPressed(Mouse::Left) && menuNum != NONE) isMenu = false;

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
	window.clear();

	return menuNum;
	////////////////////////////////////////////////////
}