#pragma once

#include <vector>

#include "gameobject.hpp"
#include "item.hpp"
#include "structure.hpp"
//#include "map.hpp" //May create circular dependency
class Map;
class Actor:public Gameobject{
friend class Map;
public:
  Actor();
  virtual bool damage(int amount); 
  virtual void heal(int amount); //TODO temp
  virtual void move(int dx, int dy); //TODO temp 
  virtual void attack(Actor & target); 
  virtual void interact(Structure * target);
  virtual bool may_act();
  //virtual void die(); //TODO temp death
 
  //TODO alex move dhis from private but that is wrong, needed here for invetory print window 
  std::vector<Item*>* get_inventory();
  virtual std::string get_data() override;
protected:
  std::vector<Item*> _inventory;
  int _hp = 1;
  int _attack = 0;
  int _defense = 0;
  int _experience = 0; //TODO define level up
  int _experience_worth = 0; //How much is this actor worth in experience?
  int _speed = 0; //a lower number is faster, it's basically "turns until next action"
  int _speed_counter = 0; //How many turns have it been idle?
};

