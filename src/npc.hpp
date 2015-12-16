#pragma once
#include "actor.hpp"


class Npc: public Actor{
public:
  Npc();
  virtual void find_path(int x, int y); //temp
  //Should include things like pathfinding
  //Probably an unnecessary step, I don't know
private:

};
