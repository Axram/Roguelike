#pragma once

#include <string>

#include "structure.hpp"

class Door:public Structure{
public:
	Door();
	Door(int x, int y);

	bool open();
	bool move();
	bool interact();
	void destroy();

};