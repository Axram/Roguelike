#include "ui.hpp"
Ui::Ui(){
	//Setting up 3+1 windows, should be more..
	int gstartx,gstarty,gheight,gwidth;
	int istartx,istarty,iheight,iwidth;
	int tstartx,tstarty,theight,twidth;
	//int ch;

	//Ncurses parameters
	initscr();
	cbreak();				//Read one char at the time
	noecho();				//Preeed button in not shown
	keypad(stdscr, TRUE);	//Enables the keyboard
	curs_set(0);			//Hide cursor
	
	//Init color mode, but its not working
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);

	gheight = 20;
	gwidth = 60;
	gstarty = 0;//(LINES - height)/2;
	gstartx = 0;//(COLS - width)/2;

	iheight = 20;
	iwidth = 20;
	istarty = 0;
	istartx = 60;

	theight = 4;
	twidth = 80;
	tstarty = 20;
	tstartx = 0;
	refresh(); // Apparently very important

	_game_win = create_newwin(gheight, gwidth, gstarty, gstartx);
	_inv_win = create_newwin(iheight, iwidth, istarty, istartx);
	_text_win = create_newwin(theight, twidth, tstarty, tstartx);
	_scroll_win = newwin(2,78,21,1);
	scrollok(_scroll_win, TRUE);
}

Ui::~Ui(){
	delwin(_game_win);
	delwin(_inv_win);
	delwin(_text_win);
	delwin(_scroll_win);
	endwin(); //Clese the game
}

WINDOW* Ui::create_newwin(int height, int width, int starty, int startx){
	WINDOW* local_win;
	local_win = newwin(height, width, starty, startx);

	//attron(COLOR_PAIR(1));
	box(local_win, 0, 0);
	//attroff(COLOR_PAIR(1));

	wrefresh(local_win);
	return local_win;
}
void Ui::destroy_win(WINDOW* local_win){
	//remvoes box around window, unreders it and destroys to window holder
	wborder(local_win,' ',' ',' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	delwin(local_win);
}
void Ui::ui_print(Map* whole_map){
	//TODO WHOLE MAP MUST BE CONST!!!
	werase(_game_win);
	Player * p = whole_map->get_player();
	int off_x = 30-p->_px; //(10,30) (y,x) is currently the middle
	int off_y = 10-p->_py;

	//std::sort(whole_map->get_gameobj()->begin(), whole_map->get_gameobj()->end(), nui_comp);
	/*
		LAMBDA, used as parameter 3 in sort
	*/
	std::sort(whole_map->get_gameobj()->begin(), whole_map->get_gameobj()->end(),
		[](const Gameobject* a, const Gameobject* b){return (a->get_depth()) < (b->get_depth());}
	);

	//Fixa depth
	for(auto i = whole_map->get_gameobj()->begin(); i != whole_map->get_gameobj()->end(); ++i){
		int print_x = (*i)->_px + off_x;
		int print_y = (*i)->_py + off_y;
		if(print_x>-1 || print_y>-1){
			mvwprintw(_game_win, print_y, print_x, "%c", (*i)->get_img());
		}
		
		char icon = (*i)->get_img();
	}
	box(_game_win, 0, 0);
	wrefresh(_game_win);
	//std::cout << "... apparently :)" << std::endl;
}
void Ui::inv_print(Player * p){
	werase(_inv_win);
  
  mvwprintw(_inv_win, 1,1 ,"    Inventory");

  //TODO remove hårdkoding
  for(int i = 2; i<20; ++i){
    mvwprintw(_inv_win,i,1,"~");
  }

  int j = 2;
  for(auto i = p->get_inventory()->begin(); i != p->get_inventory()->end(); ++i){
    std::string name = (**i).get_name();
    mvwprintw(_inv_win,j,2,"%s",name.c_str());
    ++j;
  }

  box(_inv_win, 0, 0);
  wrefresh(_inv_win);
}

//Not member function
bool nui_comp(const Gameobject* a, const Gameobject* b){
	//Depth comparasion for correct render order.
	return (a->get_depth()) < (b->get_depth());
}
