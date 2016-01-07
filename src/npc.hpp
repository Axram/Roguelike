#pragma once
#include "actor.hpp"
#include <cmath>
#include <ncurses.h>
class Npc: public Actor{
public:
  	Npc();
  	Npc(int px, int py, WINDOW * text);
  	Npc(int px, int py, int depth ,char icon, int hp, int attack, int defense, std::string name, std::string desc);
  	bool is_roaming();
private:
  	virtual void find_path(int x, int y); 
  	virtual void roam();
  	bool _roaming = true;

};
