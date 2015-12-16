#pragma once
//#ifndef CAMERA_HPP
//#define CAMERA_HPP
#include <vector>
#include "gameobject.hpp"

class Camera{
public:
  Camera(int sizex, int sizey, int posx, int posy);
  void add_gameobjects(std::vector<Gameobject> & g);
  void add_gameobjects(std::vector<Gameobject*> & g);
  void print();
  void calculate_boundaries();
  void centralize(const Gameobject & g);
private:
  
  void set_cursor(int px, int py)const;
  void clear_screen()const;
  void clear_grid();
  std::vector<std::vector<char>> _grid;
  int _size_x;
  int _size_y;
  int _pos_x;
  int _pos_y;
  int _min_x;
  int _max_x;
  int _min_y;
  int _max_y;
};

//#endif
