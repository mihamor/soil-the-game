#pragma once
#include "AbstractBlock.hpp"

class BlockFactory
{
public:
	AbstractBlock * createBlock(BlockType type, std::string blockName, std::string bFileName, char signature);
};