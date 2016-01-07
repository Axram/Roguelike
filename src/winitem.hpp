#pragma once

#include <string>

#include "item.hpp"
//#include "door.h"

class Winitem:public Item{
public:
	Winitem(){
		_description = "You've won!, press enter to continue";
		_name = "WINITEM";
	}
};