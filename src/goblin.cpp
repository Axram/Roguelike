#include "goblin.hpp"

Goblin::Goblin(int px, int py){
  //TODO do a proper constructor
  //TODO Goblin(inx px, int py):Enemy(proper variables):_px(px){ or some shit
  _px = px;
  _py = py;
  _img = 'g';
  _hp = 10;
  _attack = 1;
  _defense = 0;
}
