#include "player.hpp"
//#include <string>

Player::Player(int x, int y, WINDOW * text){
  _px = x;
  _py = y;
  //_hp = 10;
  //_attack = 1;
  //_depth = 2;
  //_solid = true;
  //_movable = false;
  //_name = "Player";
  //_desc = "It's a me";
  //_img = '@';
  _textbox = text;
}

void Player::move(int dx, int dy){
	_px += dx;
  _py += dy;
  std::string prn_str = _name + " moves to " + std::to_string(_px)+ ";"+ std::to_string(_py) + ".";
  scroll(_textbox);
  mvwprintw(_textbox, 1,1, "%s", prn_str.c_str());
  wrefresh(_textbox);
}
void Player::heal(int amount){
  for (auto i = _inventory.begin(); i != _inventory.end(); ++i){
    if((**i).get_name() == "healing potion"){
      _hp += amount;
      delete(*i);
      _inventory.erase(i);
      std::string prn_str = _name + " heals " + std::to_string(amount) + " hp.";
      scroll(_textbox);
      mvwprintw(_textbox, 1,1, "%s", prn_str.c_str());
      wrefresh(_textbox);
      break;
    }
  }
}
bool Player::has_won(){
  for(auto i = _inventory.begin(); i != _inventory.end(); ++i){
    if((**i).get_name() == "winitem"){
      std::string prn_str = "Mario gives the chalice to the Altar, victory is imminent";
      scroll(_textbox);
      mvwprintw(_textbox, 1,1, "%s", prn_str.c_str());
      wrefresh(_textbox);
      return true;
    }
  }
  return false;
}

