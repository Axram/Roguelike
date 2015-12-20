
#include "actor.hpp"
Actor::Actor(){};

void Actor::move(int dx, int dy){ //Player uses its own move with added prints

    _px += dx;
    _py += dy;
     _textbox->add_row(_name + " moves to " + std::to_string(_px) +";" +std::to_string(_py)+ ".");
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
  _textbox->add_row(_name + " is dealt " + std::to_string(resulting_damage) + " damage!");
  if(_hp <= 0){ 
    _textbox->add_row(_name + " dies!");
    _to_be_removed = true;
    return true;
  }
  return false;
}

void Actor::heal(int amount){

}

void Actor::attack(Actor & target){
  _textbox->add_row(_name + " attacks " + target.get_name() + "."); 
  target.damage(_attack);
  //return target.damage(_attack);
}

std::vector<Item*>* Actor::get_inventory(){
  return & _inventory;
}
void Actor::interact(Structure * target){
  _textbox->add_row(_name + " interacts with " + target->get_name() + ".");
  target->interact(&_inventory);
}