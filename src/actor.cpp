
#include "actor.hpp"
Actor::Actor(){};
Actor::~Actor(){
  for(auto i = _inventory.begin(); i != _inventory.end(); ++i){
    delete *i;
  }
}

void Actor::move(int dx, int dy){ //Player uses its own move with added prints

    _px += dx;
    _py += dy;
    //_textbox->add_row(_name + " moves to " + std::to_string(_px) +";" +std::to_string(_py)+ ".");
    std::string out_str = _name + " moves to " + std::to_string(_px) +";" +std::to_string(_py)+ ".";
    scroll(_textbox);
    mvwprintw(_textbox,1,1, "%s", out_str.c_str());
    wrefresh(_textbox);
}


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
  //_textbox->add_row(_name + " is dealt " + std::to_string(resulting_damage) + " damage!");
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
  //_textbox->add_row(_name + " attacks " + target.get_name() + "."); 
    std::string out_str = _name + " attacks " + target.get_name() + ".";
  scroll(_textbox);
  mvwprintw(_textbox,1,1, "%s", out_str.c_str());
  wrefresh(_textbox);
  target.damage(_attack);
  //return target.damage(_attack);
}

std::vector<Item*>* Actor::get_inventory(){
  return & _inventory;
}
std::string Actor::get_data(){
  std::string return_data;
  return_data += _name+'\n';
  return_data += std::to_string(_px)+'\n';
  return_data += std::to_string(_py)+'\n';
  return_data += std::to_string(_hp)+'\n';
  return_data += std::to_string(_experience)+'\n';
  for(auto i = _inventory.begin(); i != _inventory.end(); ++i){
    return_data += (**i)._name + '\n';
  }
  return_data += "$\n";
  return return_data;
}
void Actor::interact(Structure * target){
  //_textbox->add_row(_name + " interacts with " + target->get_name() + ".");
  std::string out_str = _name + " interacts with " + target->get_name() + ".";
  scroll(_textbox);
  mvwprintw(_textbox,1,1, "%s", out_str.c_str());
  wrefresh(_textbox);
  target->interact(&_inventory);
}