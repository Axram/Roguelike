
#include <string>
#include "gameobject.hpp"

Gameobject::Gameobject(){}
Gameobject::Gameobject(int px, int py){
  _px = px;
  _py = py;
}
Gameobject::Gameobject(int px, int py, int depth, char img, bool solid, bool movable, std::string name, std::string desc){
  _px = px;
  _py = py;
  _depth = depth;
  _img = img;
  _solid = solid;
  _movable = movable;
  _name = name;
  _desc = desc;
}

bool Gameobject::operator<(const Gameobject & b){
  return _depth < b._depth;

}




