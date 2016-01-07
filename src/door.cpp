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
std::string Door::get_data(){
	std::string return_data;
	return_data += _name+'\n';
	return_data += std::to_string(_px)+'\n';
	return_data += std::to_string(_py)+'\n';
	return_data += std::to_string(_solid) +'\n';
	return return_data;
}
bool Door::interact(std::vector<Item*>* inventory){
	for(auto i = inventory->begin(); i != inventory->end(); ++i){
      if((**i).get_name() == "doorkey" || (**i).get_name() == "Doorkey"){
			
			scroll(_textbox);
			mvwprintw(_textbox,1,1, "The door opens!");
			wrefresh(_textbox);
			scroll(_textbox);
			mvwprintw(_textbox,1,1, "The key is consumed.");
			wrefresh(_textbox);
			
			delete(*i);
			inventory->erase(i);
			return open();
		}	
	}
	//_textbox->add_row("The " + _name + " requires a key.");
	
	std::string out_str = "The " + _name + " requires a key.";
	scroll(_textbox);
	mvwprintw(_textbox,1,1, "%s", out_str.c_str());
	wrefresh(_textbox);
	
	return false;
}

bool Door::open(){
	_solid = false;
	_img = 'd';
	_desc = "Open door";
	return true;
}
