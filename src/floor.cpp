#include "floor.hpp"

Floor::Floor(int x, int y):Gameobject(x, y, 0, '.', false, false, "Floor", "Muddy"){
	_px = x;
	_py = y;
	_img = '.';
	_depth = 0;
	_solid = false;
}
