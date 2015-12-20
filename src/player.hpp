#include "actor.hpp"
#pragma once
//#ifndef PLAYER_HPP
//#define PLAYER_HPP

#include <string>

#include <ncurses.h>

class Player:public Actor{
public:
	Player(int x, int y, WINDOW * text);
	virtual void  move(int x, int y) override;
};
//#endif
