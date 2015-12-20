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

bool Door::interact(std::vector<Item*>* inventory){
	for(auto i = inventory->begin(); i != inventory->end(); ++i){
		if((**i)._name == "Doorkey"){
			return open();
			//TODO remove key from inventory (here or in clean up)
		}	
	}
	return false;
}

bool Door::open(){
	_solid = false;
	_img = 'd';
	_desc = "Open door";
	return true;
}