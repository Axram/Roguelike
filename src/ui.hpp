#pragma once

#include <string>

#include <ncurses.h>

#include "map.hpp"
#include "gameobject.hpp"
#include "player.hpp"

//Class that holds the varios windows for the ui;
//Any object that needs to print can acsses the public window pointers
class Ui{
  public:
  	Ui();
  	~Ui();

  	WINDOW* _game_win;
	WINDOW* _inv_win;
	WINDOW* _text_win;
	WINDOW* _scroll_win;
  //private:
  	WINDOW* create_newwin(int height, int width, int starty, int startx);
  	void destroy_win(WINDOW* local_win);
	void ui_print(Map* whole_map);
	void inv_print(Player * p);

};

//Sorts the gameobject list on depth
bool nui_comp(const Gameobject* a, const Gameobject* b);
