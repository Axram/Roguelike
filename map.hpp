
#ifndef MAP_HPP
#define MAP_HPP
#include <vector>
#include "gameobject.hpp"

class Map{
public:
  Map(int sizex, int sizey);
  add_gameobjects(std::vector<Gameobject> & g);
  print();
  
private:
  std::vector<std::vector<char>> _grid;
  int _sizex;
  int _sizey;
  int _centre;
};

#endif
