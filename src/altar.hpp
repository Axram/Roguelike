#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <ncurses.h>

#include "structure.hpp"
#include "item.hpp"
class Map;
class Altar:public Structure{
friend class Map;
public:
	Altar();
	Altar(int x, int y, WINDOW*);
	virtual bool move();
	virtual bool interact(std::vector<Item*>* inventory);
	virtual void destroy();
};