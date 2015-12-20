#include "player.hpp"
//#include <string>
Player::Player(int x, int y, Textbox * text){
  _px = x;
  _py = y;
  _attack = 1;
  _depth = 1;
  _solid = true;
  _movable = false;
  _name = "Mario";
  _desc = "It's a me";
  _img = '@';
  _textbox = text;
}

void Player::move(int dx, int dy){
	_px += dx;
    _py += dy;
    _textbox->add_row(_name + " moves to " + std::to_string(_px)+ ";"+ std::to_string(_py) + ".");
}

