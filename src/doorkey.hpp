#pragma once

#include <string>

#include "item.hpp"
//#include "door.h"

class Doorkey:public Item{
	Doorkey(){
		_description = "Open any door of your choosing";
		_name = "Doorkey";
	}
	~Doorkey(){}
	int uses = 1;

	bool use();
};