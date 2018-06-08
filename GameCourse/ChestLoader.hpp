#pragma once
#include "Chest.hpp"
#include <map>


class ChestLoader
{
public:
	static void saveChestsToXml(std::map<std::string, Chest *> dict, int slot);
	static std::map<std::string, Chest *> loadChestsFromXml(int slot, std::list <AbstractBlock *> &blocks);
};

