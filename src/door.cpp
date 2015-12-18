#include "door.hpp"

Door::Door(){
	_img = 'D';
	_movable = false;
	_name = "Door";
	_desc = "Closed door";
}

Door::Door(int x, int y){
	_img = 'D';
	_movable = false;
	_name = "Door";
	_desc = "Closed door";

	_px = x;
	_py = y;
}

bool Door::move(){
	return false;
}

void Door::destroy(){
	_to_be_removed = true;

}

bool Door::interact(){
	return open();
}

bool Door::open(){
	_solid = false;
	_img = 'd';
	_desc = "Open door";
	return true;
}