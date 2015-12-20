#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "structure.hpp"
#include "item.hpp"

class Door:public Structure{
public:
	Door();
	Door(int x, int y, Textbox * text);

	bool open();
	bool move();
	bool interact(std::vector<Item*>* inventory);
	void destroy();

};