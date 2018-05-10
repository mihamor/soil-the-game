#pragma once
#include "Inventory.hpp"
#include "Recipe.hpp"

class Workbench
{
	Inventory * inv;
	std::vector<Recipe> recepies;
public:
	Workbench(Inventory * inv, std::list<AbstractBlock*> &list) {
		this->inv = inv;
		std::vector<Slot *> vec;
		AbstractBlock * tree = AbstractBlock::getBlockFromList('t', list);
		AbstractBlock * wood = AbstractBlock::getBlockFromList('W', list);
		Slot * requ = new Slot(tree, 1);
		Slot * res = new Slot(wood, 2);
		vec.push_back(requ);
		Recipe r(vec, res);
		recepies.push_back(r);
	};
	void draw(RenderWindow & window, bool * isGui) {


		RectangleShape background(Vector2f(window.getSize().x - window.getSize().x / 2, window.getSize().y - window.getSize().y / 2));
		background.setFillColor(Color::White);
		background.setPosition(64, 64);

		window.draw(background);
		int j = 0;
		for (Recipe r : recepies) {
			int posx = 70;
			int posy = 70;
			int i = 0;
			for (Slot * s : r.getRequired()) {
				RectangleShape slotToDraw = s->block->rectangle; // background of slot
				slotToDraw.setPosition(posx + i * 32, posy + j * 32);
				i++;
				window.draw(slotToDraw);
			}
			RectangleShape slotToDraw = r.getResult()->block->rectangle; // background of slot
			slotToDraw.setPosition(posx + i * 64, posy + j * 32);
			window.draw(slotToDraw);
			j++;
			
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) *isGui = false;
	}
};

