#include "gameobject.hpp"
#include "wall.hpp"
#include <string>

Wall::Wall(int px, int py, char img){
  _pos.x = px;
  _pos.y = py;
  _img = img;
}
