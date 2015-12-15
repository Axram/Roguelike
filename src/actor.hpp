#include "gameobject.hpp"

#ifndef ACTOR_HPP
#define ACTOR_HPP
//#include "map.hpp"
//class Map;

class Actor:public Gameobject{
public:
  Actor();
  Actor(int px, int py, char icon, int hp, int attack, int defense);
  void damage(int amount); //temp, possible functions to add
  void heal(int amount); //temp
  void move(int dx, int dy); //temp 
  void attack(Actor & target); //temp
  
  //vector<Item> inventory = [];
private:
  int _hp = 1;
  int _attack = 1;
  int _defense = 1;
};
#endif
