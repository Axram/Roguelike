#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <ncurses.h>

#include "structure.hpp"
#include "item.hpp"
class Map;
class Door:public Structure{
friend class Map;
public:
	Door();
	Door(int x, int y, WINDOW * text);

	bool open();
	bool move();
	bool interact(std::vector<Item*>* inventory);
	void destroy();
	virtual std::string get_data() override;
};