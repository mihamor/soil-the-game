#pragma once
#include "Inventory.hpp"
#include "Recipe.hpp"
#include "tinyxml.h"
#include "WorldDef.h"

class Workbench
{
	Inventory * inv;
	std::vector<Recipe> recepies;

	static String intToStr(int value);
	bool isRectClicked(sf::RectangleShape &rectToClick, sf::RenderWindow &window);
public:
	Workbench(Inventory * inv, std::list<AbstractBlock*> &list, std::string fileName);
	~Workbench();
	void draw(RenderWindow & window, int vmodey, int vmodex, bool * isGui, HudItems * items);
	void load(std::list<AbstractBlock*> &blocks, std::string fileName);
	void workbenchSave(std::string fileName);
private:

	
};

