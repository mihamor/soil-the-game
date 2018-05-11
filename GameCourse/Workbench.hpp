#pragma once
#include "Inventory.hpp"
#include "Recipe.hpp"
#include "tinyxml.h"

class Workbench
{
	Inventory * inv;
	std::vector<Recipe> recepies;

	static String intToStr(int value) {
		std::string str = std::to_string(value);
		String result(str);
		return result;
	}
public:
	Workbench(Inventory * inv, std::list<AbstractBlock*> &list) {
		this->inv = inv;
		/*std::vector<Slot *> vec;
		AbstractBlock * tree = AbstractBlock::getBlockFromList('t', list);
		AbstractBlock * wood = AbstractBlock::getBlockFromList('W', list);
		Slot * requ = new Slot(tree, 1);
		Slot * res = new Slot(wood, 2);
		vec.push_back(requ);
		Recipe r(vec, res);
		recepies.push_back(r);*/
		load(list, "recipes.xml");
	};
	~Workbench() {
		for (Recipe r : recepies) {
			for (Slot * req : r.getRequired()) {
				delete req;
			}
			delete r.getResult();
		}
	};
	void draw(RenderWindow & window, int vmodey, int vmodex, bool * isGui) {


		RectangleShape background(Vector2f(vmodex - vmodex / 2, vmodey - vmodey / 2));
		background.setFillColor(Color::White);
		background.setPosition(64, 64);



		std::vector<RectangleShape> results;
		Text  amountShow;   //amount of slot
		Font font;
		if (!font.loadFromFile("fonts/arial.ttf"))
		{
			assert(0);
		}
		//String ss = intToStr(s->amount);
		amountShow.setFont(font);
		//amountShow.setString(ss);
		amountShow.setFillColor(Color::Black);
		amountShow.setCharacterSize(32);
		//amountShow.setPosition(posx, posy);
		Text arrow;
		arrow.setFont(font);
		arrow.setFillColor(Color::Black);
		arrow.setCharacterSize(32);
		arrow.setString(String("->"));

		window.draw(background);
		int posy = 70;
		for (Recipe r : recepies) {
			
			int posx = 70;
			if (r.ifMatchesInv(*inv)) {
				for (Slot * s : r.getRequired()) {
					RectangleShape slotToDraw = s->block->rectangle; // background of slot
					posx = posx + BLOCK_SIZE;
					slotToDraw.setPosition(posx, posy);
					amountShow.setString(intToStr(s->amount));
					amountShow.setPosition(posx, posy);
					window.draw(slotToDraw);
					window.draw(amountShow);
					
				}
				posx = posx + BLOCK_SIZE;
				arrow.setPosition(posx, posy);
				window.draw(arrow);

				Slot * result = r.getResult();
				RectangleShape resultSlot = result->block->rectangle; // background of slot
				results.push_back(resultSlot);
				posx = posx + BLOCK_SIZE;
				
				resultSlot.setPosition(posx, posy);
				amountShow.setString(intToStr(result->amount));
				amountShow.setPosition(posx, posy);
				window.draw(resultSlot);
				window.draw(amountShow);
				
				posy = posy + BLOCK_SIZE;

				if (isRectClicked(resultSlot, window))
				{
					std::cout << result->amount << std::endl;
					int amount = result->amount;
					for (int i = 0; i < amount; i++) inv->addSlot(result->block);
					for (Slot * req : r.getRequired()) {
						for (int j = 0; j < req->amount; j++) inv->reduceAmount(*req->block);
					}
					sleep(milliseconds(200));
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) *isGui = false;



	}
	void load(std::list<AbstractBlock*> &blocks, std::string fileName) {
		TiXmlDocument doc(fileName.c_str());
		if (!doc.LoadFile()) abort(); //@todo error handling


		TiXmlElement * list = doc.FirstChildElement("recipes_list");

		TiXmlElement *recipe = list->FirstChildElement("recipe");
		while (recipe) {

			TiXmlElement *required = recipe->FirstChildElement("required");
			TiXmlElement *slotReq = required->FirstChildElement("slot");
			
			std::vector<Slot *> req;
			while (slotReq) {
				char signature = atoi(slotReq->Attribute("signature"));
				int amount = atoi(slotReq->Attribute("amount"));
				Slot * requ = new Slot(AbstractBlock::getBlockFromList(signature, blocks), amount);

				req.push_back(requ);
				slotReq = slotReq->NextSiblingElement("slot");
			}


			TiXmlElement *slotRes = recipe->FirstChildElement("result");
			char signature = atoi(slotRes->Attribute("signature"));
			int amount = atoi(slotRes->Attribute("amount"));
			Slot * res = new Slot(AbstractBlock::getBlockFromList(signature, blocks), amount);

			Recipe rec(req, res);
			recepies.push_back(rec);
			recipe = recipe->NextSiblingElement("recipe");
		}
	}
	void workbenchSave() {
		TiXmlDocument doc;
		TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "", "");
		doc.LinkEndChild(decl);

		TiXmlElement * list = new TiXmlElement("recipes_list");
		doc.LinkEndChild(list);

		for (Recipe r : recepies) {
			TiXmlElement * element = new TiXmlElement("recipe");
			TiXmlElement * required = new TiXmlElement("required");
			for (Slot *s : r.getRequired()) {
				TiXmlElement * slot = new TiXmlElement("slot");
				slot->SetAttribute("signature", s->block->singnature);
				slot->SetAttribute("amount", s->amount);
				required->LinkEndChild(slot);
			}
			TiXmlElement * result = new TiXmlElement("result");
			Slot * res = r.getResult();
			result->SetAttribute("signature", res->block->singnature);
			result->SetAttribute("amount", res->amount);



			element->LinkEndChild(required);
			element->LinkEndChild(result);
			list->LinkEndChild(element);
		}

		doc.SaveFile("recipes.xml");
}


private:

	bool isRectClicked(sf::RectangleShape &rectToClick, sf::RenderWindow &window) {
		sf::IntRect rect(rectToClick.getPosition().x, rectToClick.getPosition().y, rectToClick.getGlobalBounds().width,
			rectToClick.getGlobalBounds().height);
		if (rect.contains(sf::Mouse::getPosition(window)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
			return true;
		}
		return false;
	}
};

