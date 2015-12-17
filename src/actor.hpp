#pragma once
#include "gameobject.hpp"


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
  virtual void die(); //TODO temp death
  //vector<Item> inventory = [];
protected:
  int _hp = 1;
  int _attack = 1;
  int _defense = 1;
};

