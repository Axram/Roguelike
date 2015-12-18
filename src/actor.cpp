
#include "actor.hpp"
Actor::Actor(){};
Actor::Actor(int px, int py, int depth, char icon, int hp, int attack, int defense, std::string name, std::string desc):Gameobject(px, py, depth,icon, true, false, name, desc),_hp(hp), _attack(attack), _defense(defense){
  /* TODO remove this
  _px = px;
  _py = py;
  _img = icon;
  _hp = hp;
  _attack = attack;
  _defense = defense;
  _depth = 1;
  */
}

void Actor::move(int dx, int dy){
    _px += dx;
    _py += dy;
  //Has to check if it exists anything in that direction
  //Needs to ask Map 
}

bool Actor::damage(int amount){
  int resulting_damage = amount - _defense;
  if(resulting_damage < 0) resulting_damage = 0;
  _hp -= resulting_damage;
  if(_hp <= 0){ 
    _to_be_removed = true;
    return true;
  }
  return false;
}

void Actor::heal(int amount){

}

bool Actor::attack(Actor & target){
  return target.damage(_attack);
}

std::vector<Item>* Actor::get_inventory(){
  return & inventory;
}
