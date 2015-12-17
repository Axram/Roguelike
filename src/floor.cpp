#include "floor.hpp"

Floor::Floor(int x, int y){
	_px = x;
	_py = y;
	_img = '.';
	_depth = 0;
	_solid = false;
}