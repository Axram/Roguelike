
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

