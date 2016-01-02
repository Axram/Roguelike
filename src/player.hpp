#include "actor.hpp"
#pragma once

#include <string>

#include <ncurses.h>

class Player:public Actor{
public:
	Player(int x, int y, WINDOW * text);
	virtual void  move(int x, int y) override;
};
