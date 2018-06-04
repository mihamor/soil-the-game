#include "Inventory.hpp"
#include <iostream>
#include <sstream>
#include "tinyxml.h"

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

	if (!this->font.loadFromFile("fonts/arial.ttf")) assert(0 && "font not loaded");
	amountShow.setFont(font);
	amountShow.setFillColor(Color::White);
	amountShow.setCharacterSize(16);
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
				s = nullptr;
			};
			break;
		}
	}
}

void Inventory::reduceAmount(Player * p) {

	Slot * toReduce = p->getHand();
	if (toReduce == nullptr) return;
	
	for (Slot * s : slots) {
		if (s == toReduce) {
			
			s->amount--;
			if (s->amount <= 0) {
				this->added--;
				slots.remove(s);
				delete s;	
				p->setHand(nullptr);
			};
			
			break;
		}
	}
}

void Inventory::draw(float vmodex, float vmodey, RenderWindow &window, bool *isGui, Vector2i * posMouse, Player * p,HudItems & items)
{
	if (!*isGui) return;
	// отрисовка задника ивентаря
	RectangleShape background = items.invBg;
	//background.setFillColor(Color::White);
	background.setPosition(64, 64);

	//std::cout << "[Debug]: Inventory size: " << this->added << std::endl;

	//if (Keyboard::isKeyPressed(Keyboard::Escape)) *isGui = false;
	

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

		String ss = intToStr((*it)->amount);
		this->amountShow.setString(ss);
		this->amountShow.setPosition(posx, posy);

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
static std::string definePath(int slot) {
	std::string path = "saves/inv";
	switch (slot)
	{
	case 1:
		path = path + "1.xml";
		break;
	case 2:
		path = path + "2.xml";
		break;
	case 3:
		path = path + "3.xml";
		break;
	default:
		path = path + ".xml";
		break;
	}
	return path;
}

void Inventory::saveInventory(int slot)
{

	std::string path = definePath(slot);
	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(decl);

	TiXmlElement * list = new TiXmlElement("inventory");
	doc.LinkEndChild(list);

	for (Slot * s : this->slots) {
		TiXmlElement * element = new TiXmlElement("slot");
		element->SetAttribute("signature", s->block->singnature);
		element->SetAttribute("amount", s->amount);
		list->LinkEndChild(element);

	}
	doc.SaveFile(path.c_str());
}

bool Inventory::loadInventory(int slot, std::list <AbstractBlock *> &blocks) {

	this->added = 0;
	this->slots.clear();
	std::string fileName = definePath(slot);

	TiXmlDocument doc(fileName.c_str());
	if (!doc.LoadFile()) return false; //@todo error handling


	TiXmlElement * list = doc.FirstChildElement("inventory");

	TiXmlElement *slotEl = list->FirstChildElement("slot");
	int size = 0;
	while (slotEl) {

		char signature = (char)atoi(slotEl->Attribute("signature"));
		AbstractBlock * block = AbstractBlock::getBlockFromList(signature, blocks);
		int amount = atoi(slotEl->Attribute("amount"));
		Slot * newSlot = new Slot(block, amount);
		this->slots.push_back(newSlot);
		slotEl = slotEl->NextSiblingElement("slot");
		size++;
	}
	this->added = size;
	return true;
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