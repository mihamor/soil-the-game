#pragma once

#include "AbstractBlock.hpp"


class BlockLoader
{
public:
	static void saveBlocksToXml(std::list<AbstractBlock*> &vec);
	static std::list<AbstractBlock*> * loadBlocksFromXml(std::string fileName);
};

