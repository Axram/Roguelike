#include "player.hpp"
//#include <string>

Player::Player(int x, int y, WINDOW * text){
  _px = x;
  _py = y;
  _hp = 10;
  _attack = 1;
  _depth = 2;
  _solid = true;
  _movable = false;
  _name = "Player";
  _desc = "It's a me";
  _img = '@';
  _textbox = text;
}

void Player::move(int dx, int dy){
	_px += dx;
    _py += dy;
    //_textbox->add_row(_name + " moves to " + std::to_string(_px)+ ";"+ std::to_string(_py) + ".");
    std::string prn_str = _name + " moves to " + std::to_string(_px)+ ";"+ std::to_string(_py) + ".";
    //prn_str = "Move";
    scroll(_textbox);
    mvwprintw(_textbox, 1,1, "%s", prn_str.c_str());
    wrefresh(_textbox);
}

bool Player::has_won(){
  for(auto i = _inventory.begin(); i !=_inventory.end(); ++i){
    if((**i)._name == "VICTORY"){
      return true;
    }
  }
  return false;
}

