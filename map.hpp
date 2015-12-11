
#ifndef MAP_HPP
#define MAP_HPP
#include <vector>
#include "gameobject.hpp"

class Map{
public:
  Map(int sizex, int sizey);
private:
  int _sizex;
  int _sizey;
  std::vector<std::vector<Gameobject>> _map;
};

#endif
