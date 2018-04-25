#include "Inventory.hpp"
#include <iostream>
#include <sstream>

using namespace std;
static String intToStr(int value) {
	std::string str = std::to_string(value);
	std::locale locale;
	String result(str, locale);
	return result;
}

list<Slot* > * Inventory::getList()
{
	return &slots;
}

Inventory::Inventory(int maxSlots)
{
	added = 0;
	this->maxSlots = maxSlots;
}

void Inventory::addSlot(Block * pb)
{
	bool added = false;
	if (pb == NULL) return;
	for (std::list<Slot* >::iterator it = slots.begin(); it != slots.end(); it++)
	{
		if ((*it)->block->singnature == pb->singnature && !(*it)->isStacked())
		{
			(*it)->amount++;
			added = true;
			return;
		}
	}
	if (added) return;
	if (this->added >= maxSlots) return;
	Slot * newSlot = new Slot(pb, 1);
	this->added++;
	slots.push_back(newSlot);
}

void Inventory::draw(float vmodex, float vmodey, RenderWindow &window, bool *isGui, Vector2i * posMouse, Player * p)
{
	// отрисовка задника ивентаря
	RectangleShape background(Vector2f(vmodex - vmodex / 2, vmodey - vmodey / 2));
	background.setFillColor(Color::White);
	background.setPosition(64, 64);

	if (Keyboard::isKeyPressed(Keyboard::Escape)) *isGui = false;

	bool drawed = false;
	window.draw(background);
	int posy;
	int posx = posy = 2 * BLOCK_SIZE + BLOCK_SIZE / 2;
	int counter = 0;
	// отрисовка слотов
	for (std::list<Slot* >::iterator it = slots.begin(); it != slots.end(); it++)
	{

		if (counter > 4) { posx = 2 * BLOCK_SIZE + BLOCK_SIZE / 2; posy += 2 * BLOCK_SIZE; counter = 0; }

		RectangleShape slotToDraw = (*it)->block->rectangle; // background of slot
		slotToDraw.setPosition(posx, posy);

		Text  amountShow;   //amount of slot
		Font font;
		if (!font.loadFromFile("fonts/arial.ttf"))
		{
			assert(0);
		}
		String ss = intToStr((*it)->amount);
		amountShow.setFont(font);
		amountShow.setString(ss);
		amountShow.setFillColor(Color::Black);
		amountShow.setCharacterSize(32);
		amountShow.setPosition(posx, posy);

		posx += 2 * BLOCK_SIZE;
		counter++;
		window.draw(slotToDraw);
		window.draw(amountShow);

		if (isRectClicked(slotToDraw, window))
		{
			p->setHand(*it);
			break;
		}
	}
}

void Inventory::saveInventory()
{
	// @TODO saves inventory to XML format file (include TinyXML library)
}
bool Inventory::isRectClicked(sf::RectangleShape &rectToClick, sf::RenderWindow &window) {
	sf::IntRect rect(rectToClick.getPosition().x, rectToClick.getPosition().y, rectToClick.getGlobalBounds().width,
		rectToClick.getGlobalBounds().height);
	if (rect.contains(sf::Mouse::getPosition(window)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
		return true;
	}
	return false;
}