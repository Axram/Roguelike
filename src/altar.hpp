#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <ncurses.h>

#include "structure.hpp"
#include "item.hpp"
class Altar:public Structure{
public:
	Altar();
	Altar(int x, int y, WINDOW*);
	virtual bool move();
	virtual bool interact(std::vector<Item*>* inventory);
	virtual void destroy();
};