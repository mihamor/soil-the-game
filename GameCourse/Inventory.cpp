#include "Inventory.hpp"
#include <iostream>
#include <sstream>

using namespace std;
static String intToStr(int value) {
	std::string str = std::to_string(value);
	String result(str);
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

bool Inventory::isFull(AbstractBlock * pb) {
	if (this->added < this->maxSlots) {
		std::cout << "inventory is not full" << std::endl;
		return false;
	}
	else {
		for (std::list<Slot* >::iterator it = slots.begin(); it != slots.end(); it++)
		{
			if ((*it)->block->singnature == pb->singnature && !(*it)->isStacked())
				return false;
		}
			
	}
	return true;
}

void Inventory::addSlot(AbstractBlock * pb)
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

void Inventory::reduceAmount(AbstractBlock & toReduce) {
	for (Slot * s : slots) {
		if (Block::compare(s->block, &toReduce)) {
			if (--s->amount <= 0) {
				this->added--;
				slots.remove(s);
				delete s;
			};
			break;
		}
	}
}

void Inventory::reduceAmount(Slot * toReduce) {
	if (toReduce == nullptr) return;
	
	for (Slot * s : slots) {
		if (s == toReduce) {
			if (--s->amount <= 0) {
				this->added--;
				slots.remove(s);
				delete s;
			};
			break;
		}
	}
}

void Inventory::draw(float vmodex, float vmodey, RenderWindow &window, bool *isGui, Vector2i * posMouse, Player * p)
{
	// отрисовка задника ивентаря
	RectangleShape background(Vector2f( BLOCK_SIZE * 10, vmodey / 2));
	background.setFillColor(Color::White);
	background.setPosition(64, 64);

	std::cout << "[Debug]: Inventory size: " << this->added << std::endl;

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
		if (!font.loadFromFile("fonts/arial.ttf")) assert(0 && "font not loaded");
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
		else if (isRectClickedToDel(slotToDraw, window)) {
			if (p->getHand() == *(it)) p->setHand(nullptr);
			it = slots.erase(it);
			this->added--;
			break;
		}
	}
}

void Inventory::saveInventory()
{
	// @TODO saves inventory to XML format file (include TinyXML library)
}
bool Inventory::isRectClicked(sf::RectangleShape &rectToClick, sf::RenderWindow &window) {

	Vector2i mpos_i = Mouse::getPosition(window);
	Vector2f mpos_f = window.mapPixelToCoords(mpos_i);
	Vector2i a = Vector2i(mpos_f.x, mpos_f.y);

	sf::IntRect rect(rectToClick.getPosition().x, rectToClick.getPosition().y, rectToClick.getGlobalBounds().width,
		rectToClick.getGlobalBounds().height);
	if (rect.contains(a) && (sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
		sleep(milliseconds(100));
		return true;
		
	}
	return false;
}
bool Inventory::isRectClickedToDel(sf::RectangleShape &rectToClick, sf::RenderWindow &window) {
	Vector2i mpos_i = Mouse::getPosition(window);
	Vector2f mpos_f = window.mapPixelToCoords(mpos_i);
	Vector2i a = Vector2i(mpos_f.x, mpos_f.y);

	sf::IntRect rect(rectToClick.getPosition().x, rectToClick.getPosition().y, rectToClick.getGlobalBounds().width,
		rectToClick.getGlobalBounds().height);
	if (rect.contains(a) && (sf::Keyboard::isKeyPressed(Keyboard::D))) {
		sleep(milliseconds(100));
		return true;
		
	}
	return false;
}