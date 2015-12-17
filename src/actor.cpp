
#include "actor.hpp"
Actor::Actor(){};
Actor::Actor(int px, int py, char icon, int hp, int attack, int defense){
  _px = px;
  _py = py;
  _img = icon;
  _hp = hp;
  _attack = attack;
  _defense = defense;
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
void Actor::die(){
  // Caller is responisble for destruction of the actor?
  _img = ' '; //TODO temp lol
  _solid = false;

  //Call drop item foo if we implement drops
}
