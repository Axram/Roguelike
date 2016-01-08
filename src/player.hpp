#include "actor.hpp"
#pragma once

#include <string>

#include <ncurses.h>

class Player:public Actor{
public:
	Player(int x, int y, WINDOW * text);
	//using Actor::Actor;
	Player(int hp, int attack, int defense, int experience, int exp_worth, int speed, int speed_c );
	virtual void  move(int x, int y) override;
	virtual void heal (int amount)override;
	virtual bool damage(int amount)override;
  bool has_won();
private:
	int _max_hp = 1;
};
