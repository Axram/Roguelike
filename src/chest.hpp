#pragma once

#include <vector>
#include <string>

#include <ncurses.h>

#include "structure.hpp"
#include "item.hpp"

#include "doorkey.hpp"
class Chest:public Structure{
public:
	Chest(int x, int y, WINDOW * text, bool temp = false);
	~Chest();
	bool interact(std::vector<Item*>* inventory);
	std::vector<Item*> * get_inventory();
	void add_item(Item * item);
	virtual std::string get_data()override;
	virtual std::string get_data_new() override;
protected:
	bool move(); 
	void destroy();
	bool _temporary = false;
	std::vector<Item*> _inventory;
};
