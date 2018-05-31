#include "BlockPackage.h"
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

	 TiXmlElement * list = doc.FirstChildElement("block_list");

	 TiXmlElement *block = list->FirstChildElement("block");
	 while (block) {

		 char signature = (char)atoi(block->Attribute("signature"));
		 std::string bFileName = block->Attribute("texture");
		 BlockType type = !strcmp(block->Attribute("type"), "Solid") ? Solid : Background;

		 AbstractBlock * b;
		 if (!strcmp(block->Attribute("type"), "DoorClosed"))
			 b = new DoorBlock(bFileName, signature, Solid);
		 else if (!strcmp(block->Attribute("type"), "DoorOpened")) {
			 b = new DoorBlock(bFileName, signature, Background);
			 b->rectangle.setFillColor(Color(105, 105, 105));
		 }
		 else if (!strcmp(block->Attribute("type"), "Tree")) {
			 b = new TreeBlock(bFileName, signature, Background);
		 }
		 else if (!strcmp(block->Attribute("type"), "Furnace")) {
			 b = new WorkbenchBlock(bFileName, signature, Solid, "furnace");
		 }
		 else if (!strcmp(block->Attribute("type"), "Workbench")) {
			 b = new WorkbenchBlock(bFileName, signature, Solid, "workbench");
		 }
		 else if (!strcmp(block->Attribute("type"), "Item")) {
			 b = new Item(bFileName, signature, Solid);
		 }
		 else if (!strcmp(block->Attribute("type"), "Spritic")) {
			 b = new SpriticBlock(bFileName, signature, Solid);
		 }
		 else if (!strcmp(block->Attribute("type"), "Ranged")) {
			 b = new Weapon(bFileName, signature, Background, Ranged);
		 }
		 else if (!strcmp(block->Attribute("type"), "Meele")) {
			 b = new Weapon(bFileName, signature, Background, Meele);
		 }
		 else if ((type == Solid || type == Background))
			 b = new Block(bFileName, signature, type);
		 result->push_back(b);
		 block = block->NextSiblingElement("block");
	 }
	 return result;
 }