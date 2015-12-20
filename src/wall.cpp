#ifndef WALL_CPP
#define WALL_CPP

#include "gameobject.hpp"
#include "wall.hpp"
#include <string>

Wall::Wall(int px, int py){
	_px = px;
	_py = py;
	_depth = 1;
	_img = '#';
	_solid = true;
	_movable = false;
	_name = "Wall";
	_desc = "Wall-y";

}
#endif
