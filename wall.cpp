#include "gameobject.hpp"
#include "wall.hpp"
#include <string>

Wall::Wall(int px, int py, char img){
  _px = px;
  _py = py;
  _img = img;
}
