#pragma once
#include "actor.hpp"
#include <cmath>
#include <ncurses.h>

class Npc: public Actor{
public:
  Npc();
  Npc(int px, int py, int depth ,char icon, int hp, int attack, int defense, std::string name, std::string desc);
  virtual void find_path(int x, int y); //temp
  //Should include things like pathfinding
  //Probably an unnecessary step, I don't know
private:

};
