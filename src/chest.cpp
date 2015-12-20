#include "chest.hpp"
#include <cassert>
Chest::Chest(int x, int y){
	_px = x;
	_py = y;

	_name = "Chest";
	_desc = "This might contain some mighty loot";
	_img = 'C';

	Doorkey * mykey = new Doorkey;
	_inventory.push_back(mykey);
}
Chest::~Chest(){
	for(auto i = _inventory.begin(); i != _inventory.end(); ++i){
		delete *i;
	}
}
bool Chest::interact(std::vector<Item*>* inventory){
	//Creates a new item and puts it in the actors inventory
	if(_inventory.size() == 0){
		return false;
	}
	//_textbox->add_row("This " + _name + " contained: ");
	for(auto i = _inventory.rbegin(); i != _inventory.rend(); ++i){
		inventory->push_back(*i);
		delete(*i);
		_inventory.pop_back(); //dosn return item :(
		return true;
	}
}

bool Chest::move(){} 
void Chest::destroy(){}