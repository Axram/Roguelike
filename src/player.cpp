#include "player.hpp"


Player::Player(int x, int y):Actor(){
  //TODO snyggare konstruktor
  _px = x;
  _py = y;
  _attack = 5;
  _depth = 1;
  _solid = true;
  _movable = false;
  _name = "Mario";
  _desc = "It's a me";
  _img = '@';
}

