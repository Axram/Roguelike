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

Player::Player(int hp, int attack, int defense, int experience, int exp_worth, int speed, int speed_c ){
  _hp = hp;
  _max_hp = hp;
  _attack = attack;
  _defense = defense;
  _experience = experience;
  _experience_worth = exp_worth;
  _speed = speed; 
  _speed_counter = speed_c;

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
      if(_hp < _max_hp){
        if(_hp + amount > _max_hp) amount = _max_hp-_hp;
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

bool Player::damage(int amount){
  Actor::damage(amount);

  std::string takendmg = " " + _name + " has " + std::to_string(_hp) + "hp left." ;
  //scroll(_textbox);
  wprintw(_textbox,"%s",takendmg.c_str());
  wrefresh(_textbox);
  return true;
}

