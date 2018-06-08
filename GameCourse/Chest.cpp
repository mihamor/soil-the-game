
#include "Chest.hpp"


static String intToStr(int value) {
	std::string str = std::to_string(value);
	String result(str);
	return result;
}

bool Chest::addSlotToList(Slot * slot) {
	if (this->added >= this->maxSlots) return false;
	this->slots.push_back(slot);
	this->added++;
	return true;
}
void Chest::draw(float vmodex, float vmodey, RenderWindow & window, bool * isGui, Vector2i * posMouse, Inventory * mainInventory, HudItems & items)
{


	if (!*isGui) return;
	// отрисовка задника ивентаря
	RectangleShape backgroundMainInv = items.invBg;
	//backgroundMainInv.setFillColor(Color::White);
	backgroundMainInv.setPosition(64, 64);

	//std::cout << "[Debug]: Inventory size: " << this->added << std::endl;

	//if (Keyboard::isKeyPressed(Keyboard::Escape)) *isGui = false;

	auto mainSlots = *(mainInventory->getList());
	window.draw(backgroundMainInv);


	int posy;
	int posx = posy = 2 * BLOCK_SIZE + BLOCK_SIZE / 2;
	int counter = 0;
	// отрисовка слотов
	for (std::list<Slot* >::iterator it = mainSlots.begin(); it != mainSlots.end(); it++)
	{

		if (counter > 4) { posx = 2 * BLOCK_SIZE + BLOCK_SIZE / 2; posy += 2 * BLOCK_SIZE; counter = 0; }

		Slot * slot = *(it);
		RectangleShape slotToDraw = slot->block->rectangle; // background of slot
		slotToDraw.setPosition(posx, posy);

		String ss = intToStr((*it)->amount);
		this->amountShow.setString(ss);
		this->amountShow.setPosition(posx, posy);

		posx += 2 * BLOCK_SIZE;
		counter++;
		window.draw(slotToDraw);
		window.draw(amountShow);

		if (isRectClicked(slotToDraw, window) && this->addSlot(slot->block)) mainInventory->reduceAmount(*slot->block);
			
	}

	RectangleShape backgroundChest = items.chestBg;
	backgroundChest.setPosition(backgroundMainInv.getSize().x + backgroundMainInv.getPosition().x + BLOCK_SIZE, backgroundMainInv.getPosition().y);
	//backgroundMainInv.setFillColor(Color::White);
	posy = 2 * BLOCK_SIZE + BLOCK_SIZE / 2;
	posx = backgroundChest.getPosition().x + BLOCK_SIZE / 2;

	

	window.draw(backgroundChest);

	counter = 0;
	for (std::list<Slot* >::iterator it = slots.begin(); it != slots.end(); it++)
	{

		if (counter > 1) { posx = backgroundChest.getPosition().x + BLOCK_SIZE / 2;  posy += 2 * BLOCK_SIZE; counter = 0; }

		RectangleShape slotToDraw = (*it)->block->rectangle; // background of slot
		slotToDraw.setPosition(posx, posy);

		String ss = intToStr((*it)->amount);
		this->amountShow.setString(ss);
		this->amountShow.setPosition(posx, posy);

		posx += 2 * BLOCK_SIZE;
		counter++;
		window.draw(slotToDraw);
		window.draw(amountShow);

		if (isRectClicked(slotToDraw, window) && mainInventory->addSlot((*it)->block)) this->reduceAmount(*(*it)->block);;
	}
	
}

Chest::Chest(int maxSlots) : Inventory(maxSlots){}


Chest::~Chest() {}
