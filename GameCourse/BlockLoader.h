#pragma once

#include "DoorBlock.h"
#include "Block.hpp"



class BlockLoader
{
public:
	static void saveBlocksToXml(std::list<AbstractBlock*> &vec) {
		std::cout << vec.size() << std::endl;
		TiXmlDocument doc;
		TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "", "");
		doc.LinkEndChild(decl);

		TiXmlElement * list = new TiXmlElement("block_list");
		doc.LinkEndChild(list);

		for (AbstractBlock * b : vec) {
			TiXmlElement * element = new TiXmlElement("block");
			if(b->interact() == doorType) element->SetAttribute("type", "Door");
			else element->SetAttribute("type", b->getCollision() ? "Solid" : "Background");
			element->SetAttribute("signature", b->singnature);
			element->SetAttribute("texture", b->getFileName().c_str());
			list->LinkEndChild(element);
		}

		doc.SaveFile("blocks.xml");
		//delete decl;
		//delete element;
	}

	static std::list<AbstractBlock*> * loadBlocksFromXml(std::string fileName) {
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
			if (!strcmp(block->Attribute("type"), "Door"))
				b = new DoorBlock(bFileName, signature, Solid); 
			else if ((type == Solid || type == Background ))
				 b = new Block(bFileName, signature, type);
			result->push_back(b);
			block = block->NextSiblingElement("block");
		}
		return result;
	}
};

