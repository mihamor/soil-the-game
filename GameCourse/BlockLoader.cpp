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

	for (AbstractBlock * block : vec) {
		TiXmlElement * element = new TiXmlElement("block");
		if (block->interact() == doorType) {
			if (block->getSingature() == doorOpenSign)
				element->SetAttribute("type", "DoorOpened");
			else  element->SetAttribute("type", "DoorClosed");
		}
		else if (block->interact() == treeType) {
			element->SetAttribute("type", "Tree");;
		}
		else if (block->interact() == craftType) {
			if (block->getSingature() == DEFAULT_BENCH_SIGN) element->SetAttribute("type", "Workbench");
			else element->SetAttribute("type", "Furnace");
		}
		else if (block->interact() == itemType) {
			element->SetAttribute("type", "Item");
		}
		else if (block->interact() == spriticType) {
			element->SetAttribute("type", "Spritic");
		}
		else if (block->interact() == weaponItemType) {
			WeaponBlock * weaponBlock = (WeaponBlock *)block;
			if(weaponBlock->getType() == Meele) element->SetAttribute("type", "Meele");
			else element->SetAttribute("type", "Ranged");
		}
		else if (block->interact() == chestType) {
			element->SetAttribute("type", "Chest");
		}
		else element->SetAttribute("type", block->getCollision() ? "Solid" : "Background");
		element->SetAttribute("signature", block->getSingature());
		element->SetAttribute("texture", block->getFileName().c_str());
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