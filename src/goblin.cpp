#include "goblin.hpp"

Goblin::Goblin(int px, int py, Textbox * text){
  _textbox = text;
  _px = px;
  _py = py;
  _img = 'g';
  _hp = 10;
  _attack = 1;
  _defense = 0;
  _speed = 2;
  _depth = 1;
  _name = "Goblin";
  _desc = "Ugly";
}
