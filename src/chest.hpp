#pragma once

#include <vector>
#include <string>

#include <ncurses.h>

#include "structure.hpp"
#include "item.hpp"

#include "doorkey.hpp"

class Chest:public Structure{
public:
	Chest(int x, int y, WINDOW * text);
	~Chest();
	bool interact(std::vector<Item*>* inventory);
	std::vector<Item*> * get_inventory();
	virtual std::string get_data()override;
protected:
	bool move(); 
	void destroy();

	std::vector<Item*> _inventory;
};
