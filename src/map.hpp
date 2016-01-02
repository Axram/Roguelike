#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <ncurses.h>
#include <map>

#include "gameobject.hpp"
#include "wall.hpp"
#include "player.hpp"
#include "goblin.hpp"
#include "enemy.hpp"
#include "floor.hpp"
#include "structure.hpp"
#include "door.hpp"
#include "chest.hpp"
#include "textbox.hpp"
#include "doorkey.hpp"
#include "winitem.hpp"
//#ifndef MAP_HPP
//#define MAP_HPP
//class Player;
//class Gameobject;
class Map{
public:
  Map(std::string filename, WINDOW*& text);
  ~Map();
  Player * get_player();
  std::vector<std::string> get_names(int x, int y); //TODO define (get the names of all the gameobjects in that position, used for commands like "look right"
  std::vector<std::string> get_descs(int x, int y); //TODO define (get descriptions of all gameobjects in that position
  std::vector<Gameobject*> & get_map();
  Enemy * get_enemy(int x, int y);
  std::vector<Enemy*> & get_enemies();
  void cleanup(); //Removes dead enemies
  void save_data(std::string);
  //void runtime_load(std::string);
  void add_item(std::vector<Item*>*, std::string);
  bool is_free(int x, int y);
  bool enemy_exists(int x, int y);
  bool structure_exists(int x, int y);
  Structure * get_structure(int x, int y);
  void find_path(Actor & hunter, Gameobject & target);

  std::vector<Gameobject*>* get_gameobj(){
    return &_go;
  }
  
private:
  void generate_map(std::string filename);
  void load_data(std::string);
  void load_data_new(std::string);
  void add_wall(int, int, int&, std::string);
  void add_player(int, int, int&, std::string);
  void add_chest(int, int, int&, std::string);
  void add_goblin(int, int, int&, std::string);
  void add_door(int, int, int&, std::string);
  void add_floor(int, int, int&, std::string);
  void load_inventory(std::vector<Item*> * inventory, std::string filename, int & item_nr);
  Player * _player = nullptr;
  //TODO alla vectorer skall vara private
  std::vector<Gameobject*> _go;
  std::vector<Enemy*> _enemies;
  std::vector<Wall*> _s;

  std::vector<Structure*> _st; //NOT CLEANED UP
  WINDOW * _textbox;
  std::map<std::string, void (Map::*) (int, int, int&, std::string)> _funkpoint;
};

//#endif
