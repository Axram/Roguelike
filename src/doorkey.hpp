#pragma once

#include <string>

#include "item.hpp"

class Doorkey:public Item{
public:
	Doorkey(){
		_description = "Open any door of your choosing";
		_name = "Doorkey";
	}
	~Doorkey(){}
	int uses = 1;

	bool use();
};