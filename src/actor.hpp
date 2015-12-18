#pragma once

#include <vector>

#include "gameobject.hpp"
#include "item.hpp"

//#include "map.hpp"
//class Map;

class Actor:public Gameobject{
public:
  friend class Map;
  Actor();
  Actor(int px, int py, int depth ,char icon, int hp, int attack, int defense, std::string name, std::string desc);
  virtual bool damage(int amount); 
  virtual void heal(int amount); //TODO temp
  virtual void move(int dx, int dy); //TODO temp 
  virtual bool attack(Actor & target); 
  //virtual void die(); //TODO temp death
  std::vector<Item> inventory;
  std::vector<Item>* get_inventory();
protected:
  int _hp;
  int _attack;
  int _defense;
};

