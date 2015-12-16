#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "gameobject.hpp"
#include "wall.hpp"
#include "player.hpp"
#include "goblin.hpp"
#include "enemy.hpp"
//#ifndef MAP_HPP
//#define MAP_HPP
//class Player;
//class Gameobject;
class Map{
public:
  Map(std::string filename);
  Player & get_player();
  std::vector<std::string> get_names(int x, int y); //TODO define (get the names of all the gameobjects in that position, used for commands like "look right"
  std::vector<std::string> get_descs(int x, int y); //TODO define (get descriptions of all gameobjects in that position
  std::vector<Gameobject*> & get_map();
  Enemy * get_enemy(int x, int y);
  void cleanup_enemies(); //Removes dead enemies
  void generate_map(std::string filename);
  std::vector<Gameobject*> _go;
  std::vector<Wall*> _walls;
  bool is_free(int x, int y);
  bool enemy_exists(int x, int y);
  Player * _player = nullptr;
  std::vector<Enemy*> _enemies;
};

//#endif
