#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <ncurses.h>

#include "structure.hpp"
#include "item.hpp"

class Door:public Structure{
public:
	Door();
	Door(int x, int y, WINDOW * text);

	bool open();
	bool move();
	bool interact(std::vector<Item*>* inventory);
	void destroy();

};