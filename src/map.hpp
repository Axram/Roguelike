#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include "gameobject.hpp"
#include "wall.hpp"
#include "player.hpp"
#include "goblin.hpp"
#include "enemy.hpp"
#include "floor.hpp"
//#ifndef MAP_HPP
//#define MAP_HPP
//class Player;
//class Gameobject;
class Map{
public:
  Map(std::string filename);
  ~Map();
  Player & get_player();
  std::vector<std::string> get_names(int x, int y); //TODO define (get the names of all the gameobjects in that position, used for commands like "look right"
  std::vector<std::string> get_descs(int x, int y); //TODO define (get descriptions of all gameobjects in that position
  std::vector<Gameobject*> & get_map();
  Enemy * get_enemy(int x, int y);
  void cleanup(); //Removes dead enemies
  void generate_map(std::string filename);
  bool is_free(int x, int y);
  bool enemy_exists(int x, int y);
  Player * _player = nullptr;

  //TODO alla vectorer skall vara private
  std::vector<Gameobject*> _go;
  std::vector<Enemy*> _enemies;
  std::vector<Wall*> _s;
};

//#endif
