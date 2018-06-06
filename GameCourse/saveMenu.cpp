#include "saveMenu.hpp"
#include "Cursor.hpp"
#include <iostream>
#include <string>
#include <fstream>

bool MENU::isEmptySlot(unsigned int slot) {

	std::string FileName;
	switch (slot)
	{
	case 1:
		FileName = "saves/map1.mf";
		break;
	case 2:
		FileName = "saves/map2.mf";
		break;
	case 3:
		FileName = "saves/map3.mf";
		break;
	default:
		assert(0 && "Unknown slot");
		break;
	}

	std::ifstream is;
	is.open(FileName.c_str(), std::ios::binary);
	if (!is.is_open()) return true;
	is.seekg(0, std::ios::end);
	int length = (int)is.tellg();
	std::cout << length << std::endl;
	is.close();
	return length <= 0;
}

static bool isPointed(IntRect button, RenderWindow & window, Vector2i a) {
	return button.contains(a);
}


saveSlotNumber saveMenu(RenderWindow & window, bool mode, int vmodex, int vmodey)
{
	GameCursor c(Vector2i(vmodex, vmodey));
	Vector2u res = Vector2u(vmodex, vmodey);
	window.clear();
	bool availableSlots[3];
	for (int i = 0; i < 3; i++) availableSlots[i] = !MENU::isEmptySlot(i + 1);

	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("menu/saveslot1.png");

	Vector2u buttonSize = menuTexture1.getSize();
	menuTexture2.loadFromFile("menu/saveslot2.png");
	menuTexture3.loadFromFile("menu/saveslot3.png");
	menuBackground.loadFromFile("menu/menubg.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menuBg(menuBackground);
	bool isMenu = 1;
	saveSlotNumber menuNum = 0;
	menu1.setPosition((res.x - buttonSize.x) / 2, res.y / 2);
	menu2.setPosition((res.x - buttonSize.x) / 2, res.y / 2 + 60);
	menu3.setPosition((res.x - buttonSize.x) / 2, res.y / 2 + 120);
	menuBg.setPosition(0, 0);

	while (isMenu)
	{
		Vector2i mpos_i = Mouse::getPosition(window);
		Vector2f mpos_f = window.mapPixelToCoords(mpos_i);
		Vector2i a = Vector2i(mpos_f.x, mpos_f.y);
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				return -2;
			}
			if (event.type == Event::Resized)
			{
			}
			if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left && menuNum != 0)
				if ((mode && availableSlots[menuNum - 1]) || !mode) isMenu = false;
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) return -1;
		}

		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (isPointed(IntRect((res.x - buttonSize.x) / 2, res.y / 2, buttonSize.x, buttonSize.y), window, a)) { menu1.setColor(availableSlots[0] ? Color::Blue : Color::Red); menuNum = 1; }
		else if (isPointed(IntRect((res.x - buttonSize.x) / 2, res.y / 2 + 60, buttonSize.x, buttonSize.y), window, a)) { menu2.setColor(availableSlots[1] ? Color::Blue : Color::Red); menuNum = 2; }
		else if (isPointed(IntRect((res.x - buttonSize.x) / 2, res.y / 2 + 120, buttonSize.x, buttonSize.y), window, a)) { menu3.setColor(availableSlots[2] ? Color::Blue : Color::Red); menuNum = 3; }
		else menuNum = 0;

		c.update(true, a, 100);

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		c.draw(window);

		window.display();
	}
	window.clear();

	return menuNum;
}
