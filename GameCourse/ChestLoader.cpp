#include "ChestLoader.hpp"
#include "tinyxml.h"
const int CHEST_SIZE = 4;
static std::string definePath(int slot) {
	std::string path = "saves/chests";
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

void ChestLoader::saveChestsToXml(std::map<std::string, Chest*> dict, int slot)
{
	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(decl);

	TiXmlElement * list = new TiXmlElement("chest_list");
	doc.LinkEndChild(list);

	for (auto val : dict)
	{
		Chest * chest = val.second;
		std::string key = val.first;
		TiXmlElement * chestElement = new TiXmlElement("chest");
		chestElement->SetAttribute("key", key.c_str());
		//..
		auto chestContent = chest->getList();
		for (auto slot : *chestContent) {
			TiXmlElement * slotElement = new TiXmlElement("slot");
			slotElement->SetAttribute("signature", slot->block->singnature);
			slotElement->SetAttribute("amount", slot->amount);
			chestElement->LinkEndChild(slotElement);
		}
		list->LinkEndChild(chestElement);
	}
	doc.SaveFile(definePath(slot).c_str());
}

std::map<std::string, Chest*> ChestLoader::loadChestsFromXml(int slot, std::list <AbstractBlock *> &blocks)
{
	std::map<std::string, Chest*> newDict;
	TiXmlDocument doc(definePath(slot).c_str());
	if (!doc.LoadFile()) return newDict;
	std::string debugLoader = "[Debug LOADER]: ";
	std::cout << debugLoader << "POSHLO POEHALO" << std::endl;
	TiXmlElement * list = doc.FirstChildElement("chest_list");
	TiXmlElement *chest = list->FirstChildElement("chest");
	while (chest) {
		std::string key = chest->Attribute("key");
		Chest * newVal = new Chest(CHEST_SIZE);
		std::cout << debugLoader << key << std::endl;
		TiXmlElement * slot = chest->FirstChildElement("slot");
		while (slot){
			int amount = atoi(slot->Attribute("amount"));
			char signature = (char)atoi(slot->Attribute("signature"));
			std::cout << debugLoader << signature <<  ", "<< amount<<  std::endl;
			AbstractBlock * block = AbstractBlock::getBlockFromList(signature, blocks);
			Slot * newSlot = new Slot(block, amount);
			newVal->addSlotToList(newSlot);
			slot = slot->NextSiblingElement("slot");
		}

		newDict[key] = newVal;
		chest = chest->NextSiblingElement("chest");
	}
	return newDict;
}
