#include <string>
#include "gameobject.hpp"

Gameobject::Gameobject(){}
Gameobject::Gameobject(int px, int py){
  _pos.x = px;
  _pos.y = py;
}
Gameobject::Gameobject(int px, int py, char img, bool solid, bool movable, std::string name, std::string desc){
  _pos.x = px;
  _pos.y = py;
  _img = img;
  _solid = solid;
  _movable = movable;
  _name = name;
  _desc = desc;
}





