#include "chest.hpp"
#include <cassert>
Chest::Chest(int x, int y, WINDOW * text, bool temp){
	_px = x;
	_py = y;
	_temporary = temp;
	_textbox = text;
	_name = "Chest";
	_desc = "This might contain some mighty loot";
	_img = 'C';
}
Chest::~Chest(){
	for(auto i = _inventory.begin(); i != _inventory.end(); ++i){
		delete *i;
	}
}

std::vector<Item*>* Chest::get_inventory(){
	return &_inventory;
}
void Chest::add_item(Item * item){
	_inventory.push_back(item);
}
std::string Chest::get_data(){
	std::string return_data;
	return_data += _name+'\n';
	return_data += std::to_string(_px)+'\n';
	return_data += std::to_string(_py)+'\n';
	for(auto i = _inventory.begin(); i != _inventory.end(); ++i){
      return_data += (**i).get_name() + '\n';
    }
    return_data += "$\n";
    return return_data;
}

std::string Chest::get_data_new(){
	std::string s;
 	s += Gameobject::get_data_new();
  	for(auto i = _inventory.begin(); i != _inventory.end(); ++i){
      s += (**i).get_name() + '\n';
  	}
  	s += "$\n";
  	return s;
}

bool Chest::interact(std::vector<Item*>* inventory){
	//Creates a new item and puts it in the actors inventory
	if(_inventory.size() == 0){
		std::string prn_str = "The " + _name + " is empty.";
		scroll(_textbox);
    	mvwprintw(_textbox, 1,1, "%s", prn_str.c_str());
    	wrefresh(_textbox);
    	if(_temporary) _to_be_removed = true;
		return false;
	}
	for(auto i = _inventory.rbegin(); i != _inventory.rend(); ++i){
		inventory->push_back(*i);
		
		std::string prn_str = (**i).get_name();
		scroll(_textbox);
    	mvwprintw(_textbox, 1,1, "%s", prn_str.c_str());
    	wrefresh(_textbox);
		
		_inventory.pop_back();
		return true;
	}
	return false;
}

bool Chest::move(){return false;} 
void Chest::destroy(){}
