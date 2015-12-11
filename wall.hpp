#ifndef WALL_HPP
#define WALL_HPP

#include "gameobject.hpp"

class Wall:public Gameobject{
public:
  Wall(int px, int py, char img = '#');
private:
};

#endif
