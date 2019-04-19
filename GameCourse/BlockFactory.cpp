#include "BlockFactory.hpp"
#include "BlockPackage.h"

AbstractBlock * BlockFactory::createBlock(BlockType type, std::string blockName, std::string bFileName, char signature)
{
	AbstractBlock * newBlock = NULL;
	if (blockName == "DoorClosed")
		newBlock = new DoorBlock(bFileName, signature, Solid);
	else if (blockName == "DoorOpened") {
		newBlock = new DoorBlock(bFileName, signature, Background);
		newBlock->getRectangleShape()->setFillColor(Color(105, 105, 105));
	}
	else if (blockName == "Tree")
		newBlock = new TreeBlock(bFileName, signature, Background);
	else if (blockName == "Furnace")
		newBlock = new WorkbenchBlock(bFileName, signature, Solid, "furnace");
	else if (blockName == "Workbench") 
		newBlock = new WorkbenchBlock(bFileName, signature, Solid, "workbench");
	else if (blockName ==  "Item") 
		newBlock = new Item(bFileName, signature, Solid);
	else if (blockName == "Chest") 
		newBlock = new ChestBlock(bFileName, signature, Solid);
	else if (blockName == "Spritic")
		newBlock = new SpriticBlock(bFileName, signature, Solid);
	else if (blockName == "Ranged")
		newBlock = new WeaponBlock(bFileName, signature, Background, Ranged);
	else if (blockName == "Meele")
		newBlock = new WeaponBlock(bFileName, signature, Background, Meele);
	else if ((type == Solid || type == Background))
		newBlock = new Block(bFileName, signature, type);

	return newBlock;
}
