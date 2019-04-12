#include "BlockPackage.h"
#include "BlockFactory.hpp"
#include <iostream>

 void BlockLoader::saveBlocksToXml(std::list<AbstractBlock*> &vec) {
	std::cout << vec.size() << std::endl;
	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(decl);

	TiXmlElement * list = new TiXmlElement("block_list");
	doc.LinkEndChild(list);

	for (AbstractBlock * b : vec) {
		TiXmlElement * element = new TiXmlElement("block");
		if (b->interact() == doorType) {
			if (b->singnature == doorOpenSign)
				element->SetAttribute("type", "DoorOpened");
			else  element->SetAttribute("type", "DoorClosed");
		}
		else if (b->interact() == treeType) {
			element->SetAttribute("type", "Tree");;
		}
		else if (b->interact() == craftType) {
			if (b->singnature == DEFAULT_BENCH_SIGN) element->SetAttribute("type", "Workbench");
			else element->SetAttribute("type", "Furnace");
		}
		else if (b->interact() == itemType) {
			element->SetAttribute("type", "Item");
		}
		else if (b->interact() == spriticType) {
			element->SetAttribute("type", "Spritic");
		}
		else if (b->interact() == weaponItemType) {
			Weapon * w = (Weapon *)b;
			if(w->getType() == Meele) element->SetAttribute("type", "Meele");
			else element->SetAttribute("type", "Ranged");
		}
		else if (b->interact() == chestType) {
			element->SetAttribute("type", "Chest");
		}
		else element->SetAttribute("type", b->getCollision() ? "Solid" : "Background");
		element->SetAttribute("signature", b->singnature);
		element->SetAttribute("texture", b->getFileName().c_str());
		list->LinkEndChild(element);
	}

	doc.SaveFile("blocks.xml");
}

 std::list<AbstractBlock*> *  BlockLoader::loadBlocksFromXml(std::string fileName) {
	 TiXmlDocument doc(fileName.c_str());
	 if (!doc.LoadFile()) abort(); //@todo error handling

	 auto result = new std::list<AbstractBlock *>();
	 BlockFactory * factory = new BlockFactory();


	 TiXmlElement * list = doc.FirstChildElement("block_list");

	 TiXmlElement *block = list->FirstChildElement("block");
	 while (block) {

		 char signature = (char)atoi(block->Attribute("signature"));
		 std::string bFileName = block->Attribute("texture");
		 std::string blockName = block->Attribute("type");
		 BlockType type = blockName == "Solid" ? Solid : Background;
		 
		 AbstractBlock * b = factory->createBlock(type, blockName, bFileName, signature);

		 result->push_back(b);
		 block = block->NextSiblingElement("block");
	 }
	 return result;
 }