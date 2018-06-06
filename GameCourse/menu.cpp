#include "menu.hpp"
#include "Cursor.hpp"

MenuChoiceCustom menu(RenderWindow & window, int vmodex, int vmodey)
{
	GameCursor c(Vector2i(vmodex, vmodey));
	bool resized = false;
	Vector2u res = Vector2u(vmodex, vmodey);

	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("menu/continue.png");

	Vector2u buttonSize = menuTexture1.getSize();
	menuTexture2.loadFromFile("menu/newgame.png");
	menuTexture3.loadFromFile("menu/exit.png");
	//aboutTexture.loadFromFile("images/about.png");
	menuBackground.loadFromFile("menu/menubg.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), /*about(aboutTexture),*/ menuBg(menuBackground);
	bool isMenu = 1;
	MenuChoiceCustom menuNum = NONE;
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
				window.close();
				return EXIT;
			}
			if (event.type == Event::Resized)
			{
				resized = true;

			}if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left && menuNum != NONE) isMenu = false;
		}

		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = NONE;
		window.clear(Color(129, 181, 221));



		if (IntRect((res.x - buttonSize.x) / 2, res.y / 2, buttonSize.x, buttonSize.y).contains(a)) { menu1.setColor(Color::Blue); menuNum = CONTINUE; }
		else if (IntRect((res.x - buttonSize.x) / 2, res.y / 2 + 60, buttonSize.x, buttonSize.y).contains(a)) { menu2.setColor(Color::Blue); menuNum = NEWGAME; }
		else if (IntRect((res.x - buttonSize.x) / 2, res.y / 2 + 120, buttonSize.x, buttonSize.y).contains(a)) { menu3.setColor(Color::Blue); menuNum = EXIT; }
		else menuNum = NONE;


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