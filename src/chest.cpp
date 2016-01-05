#include "chest.hpp"
#include <cassert>
Chest::Chest(int x, int y, WINDOW * text){
	_px = x;
	_py = y;
	_textbox = text;
	_name = "Chest";
	_desc = "This might contain some mighty loot";
	_img = 'C';
	//Doorkey * mykey = new Doorkey;
	//_inventory.push_back(mykey);
}
Chest::~Chest(){
	for(auto i = _inventory.begin(); i != _inventory.end(); ++i){
		delete *i;
	}
}

std::vector<Item*>* Chest::get_inventory(){
	return &_inventory;
}
std::string Chest::get_data(){
	std::string return_data;
	return_data += _name+'\n';
	return_data += std::to_string(_px)+'\n';
	return_data += std::to_string(_py)+'\n';
	for(auto i = _inventory.begin(); i != _inventory.end(); ++i){
    	return_data += (**i)._name + '\n';
    }
    return_data += "$\n";
    return return_data;
}

std::string Chest::get_data_new(){
	std::string s;
 	s += Gameobject::get_data_new();
  	for(auto i = _inventory.begin(); i != _inventory.end(); ++i){
    	s += (**i)._name + '\n';
  	}
  	s += "$\n";
  	return s;
}

bool Chest::interact(std::vector<Item*>* inventory){
	//Creates a new item and puts it in the actors inventory
	if(_inventory.size() == 0){
		//_textbox->add_row("The " + _name + " is empty.");
		std::string prn_str = "The " + _name + " is empty.";
		scroll(_textbox);
    	mvwprintw(_textbox, 1,1, "%s", prn_str.c_str());
    	wrefresh(_textbox);
    	if(_temporary) _to_be_removed = true;
		return false;
	}
	//_textbox->add_row("This " + _name + " contained: ");
	for(auto i = _inventory.rbegin(); i != _inventory.rend(); ++i){
		inventory->push_back(*i);
		
		//_textbox->add_row((**i)._name);
		std::string prn_str = (**i)._name;
		scroll(_textbox);
    	mvwprintw(_textbox, 1,1, "%s", prn_str.c_str());
    	wrefresh(_textbox);
		
		_inventory.pop_back(); //dosn return item :(
		return true;
	}
}

bool Chest::move(){} 
void Chest::destroy(){}