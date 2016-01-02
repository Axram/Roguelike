#pragma once

#include <string>

#include "item.hpp"
//#include "door.h"

class Winitem:public Item{
public:
	Winitem(){
		_description = "I've won!";
		_name = "WINITEM";
	}
};