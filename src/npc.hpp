#pragma once
#include "actor.hpp"
#include <cmath>
#include <ncurses.h>
class Map;
class Npc: public Actor{
public:
	friend class Map;
  	Npc();
  	Npc(int px, int py, WINDOW * text);
  	Npc(int px, int py, int depth ,char icon, int hp, int attack, int defense, std::string name, std::string desc);
  	bool is_roaming();
  //Should include things like pathfinding
  //Probably an unnecessary step, I don't know
private:
  	virtual void find_path(int x, int y); //temp
  	virtual void roam();
  	bool _roaming = true;

};
