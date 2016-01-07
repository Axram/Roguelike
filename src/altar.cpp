#include "altar.hpp"

Altar::Altar(){
	_img = 'A';
	_movable = false;
	_name = "Altar";
	_desc = "The temple gods altar";
}

Altar::Altar(int x, int y, WINDOW* text){
	_img = 'A';
	_movable = false;
	_name = "Altar";
	_desc = "The temple gods altar";
	_textbox = text;
	_px = x;
	_py = y;
}

bool Altar::move(){return false;}

bool Altar::interact(std::vector<Item*>* inventory){
	for(auto i = inventory->begin(); i != inventory->end(); ++i){
		if((**i).get_name() == "chalice of doom"){
			
			delete(*i);
			inventory->erase(i);
			Item * win = new Item("winitem");
			inventory->push_back(win);
			return true;
		}
	}
	return false;
}
void Altar::destroy(){}

