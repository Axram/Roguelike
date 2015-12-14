
#ifndef MAP_HPP
#define MAP_HPP
#include <vector>
#include "gameobject.hpp"

class Map{
public:
  Map(int sizex, int sizey, int topx, int topy);
  void add_gameobjects(std::vector<Gameobject> & g);
  void print();
  void calculate_boundaries();
//private:
  
  void set_cursor(int px, int py);
  void clear_screen();
  std::vector<std::vector<char>> _grid;
  int _size_x;
  int _size_y;
  int _top_x;
  int _top_y;
  int _min_x;
  int _max_x;
  int _min_y;
  int _max_y;
};

#endif
