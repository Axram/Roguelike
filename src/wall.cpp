#ifndef WALL_CPP
#define WALL_CPP

#include "gameobject.hpp"
#include "wall.hpp"
#include <string>

Wall::Wall(int px, int py):Gameobject(0, 0, 1, '#', true, false, "Wall", "Wall-y"){
  _px = px;
  _py = py;
}
#endif
