#include "actor.hpp"
#pragma once
//#ifndef PLAYER_HPP
//#define PLAYER_HPP


class Player:public Actor{
public:
	Player(int x, int y, Textbox * text);
	virtual void  move(int x, int y) override;
};
//#endif
