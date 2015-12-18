#pragma once

#include <vector>
#include <string>

#include "structure.hpp"
#include "item.hpp"

#include "doorkey.hpp"

class Chest:public Structure{
public:
	Chest(int x, int y);
	bool interact(std::vector<Item>* inventory);
protected:
	bool move(); 
	void destroy();

	std::vector<Item> _inventory;
};