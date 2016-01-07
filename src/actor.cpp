
#include "actor.hpp"


void Actor::move(int dx, int dy){ //Player uses its own move with added prints

    _px += dx;
    _py += dy;
    std::string out_str = _name + " moves to " + std::to_string(_px) +";" +std::to_string(_py)+ ".";
    scroll(_textbox);
    mvwprintw(_textbox,1,1, "%s", out_str.c_str());
    wrefresh(_textbox);
}
/*
void Actor::set_vars(int hp, int attack, int defense, int experience, int exp_worth, int speed, int speed_c){
  _hp = hp;
  _attack = attack;
  _defense = defense;
  _experience = experience;
  _experience_worth = exp_worth;
  _speed = speed;
  _speed_counter = speed_c;

}
*/
bool Actor::may_act(){
  ++_speed_counter;
  if(_speed_counter > _speed){
    _speed_counter = 0;
    return true;
  }
  return false;
}
bool Actor::damage(int amount){
  int resulting_damage = amount - _defense;
  if(resulting_damage < 0) resulting_damage = 0;
  _hp -= resulting_damage;
    std::string out_str = _name + " is dealt " + std::to_string(resulting_damage) + " damage!";
  scroll(_textbox);
  mvwprintw(_textbox,1,1, "%s", out_str.c_str());
  wrefresh(_textbox);

  if(_hp <= 0){ 
    std::string out_str = _name + " dies!";
    scroll(_textbox);
    mvwprintw(_textbox,1,1, "%s", out_str.c_str());
    wrefresh(_textbox);

    _to_be_removed = true;
    return true;
  }
  return false;
}

void Actor::heal(int amount){

}

void Actor::attack(Actor & target){
    std::string out_str = _name + " attacks " + target.get_name() + ".";
  scroll(_textbox);
  mvwprintw(_textbox,1,1, "%s", out_str.c_str());
  wrefresh(_textbox);
  target.damage(_attack);
}

std::vector<Item*>* Actor::get_inventory(){
  return & _inventory;
}
void Actor::add_item(Item * newitem){
  _inventory.push_back(newitem);
}
void Actor::interact(Structure * target){
  std::string out_str = _name + " interacts with " + target->get_name() + ".";
  scroll(_textbox);
  mvwprintw(_textbox,1,1, "%s", out_str.c_str());
  wrefresh(_textbox);
  target->interact(&_inventory);
}

std::string Actor::get_data(){
  std::string return_data;
  return_data += _name+'\n';
  return_data += std::to_string(_px)+'\n';
  return_data += std::to_string(_py)+'\n';
  return_data += std::to_string(_hp)+'\n';
  return_data += std::to_string(_experience)+'\n';
  for(auto i = _inventory.begin(); i != _inventory.end(); ++i){
    return_data += (**i).get_name() + '\n';
  }
  return_data += "$\n";
  return return_data;
}

std::string Actor::get_data_new(){
  std::string s = "";
  s += Gameobject::get_data_new();
  s += std::to_string(_hp) + '\n';
  s += std::to_string(_attack) + '\n';
  s += std::to_string(_defense) + '\n';
  s += std::to_string(_experience) + '\n';
  s += std::to_string(_experience_worth) + '\n';
  s += std::to_string(_speed) + '\n';
  s += std::to_string(_speed_counter) + '\n';
  for(auto i = _inventory.begin(); i != _inventory.end(); ++i){
    s += (**i).get_name() + '\n';
  }
  s += "$\n";
  return s;
}

void Actor::remove_items(){
  for(auto i = _inventory.begin(); i != _inventory.end(); ++i){
    delete *i;
  }
}
