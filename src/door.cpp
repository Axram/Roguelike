#include "door.hpp"

Door::Door(){
	_img = 'D';
	_movable = false;
	_name = "Door";
	_desc = "Closed door";
}

Door::Door(int x, int y, WINDOW * text){
	_img = 'D';
	_movable = false;
	_name = "Door";
	_desc = "Closed door";
	_textbox = text;
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
			//_textbox->add_row("The " + _name + " opens!");
			//_textbox->add_row("The " + (**i)._name + " is used up.");
			
			scroll(_textbox);
			mvwprintw(_textbox,0,1, "I am DOOR");
			wrefresh(_textbox);
			scroll(_textbox);
			mvwprintw(_textbox,0,1, "Out of key");
			wrefresh(_textbox);
			
			delete(*i);
			inventory->erase(i);
			return open();
		}	
	}
	//_textbox->add_row("The " + _name + " requires a key.");
	return false;
}

bool Door::open(){
	_solid = false;
	_img = 'd';
	_desc = "Open door";
	return true;
}