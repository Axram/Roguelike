#include "gameobject.hpp"
#include "camera.hpp"
#include "wall.hpp"
#include "functions.cpp"
#include "player.hpp"
#include "map.hpp"
#include "goblin.hpp"
#include "textbox.hpp"

#include <ncurses.h>

#include <vector>
#include <string>
#include <iostream>

std::string main_menu(void){
  //Make a main menu where yoy choose new game or load game from file, maybe?
  
}

WINDOW* create_newwin(int height, int width, int starty, int startx){
	WINDOW* local_win;
	local_win = newwin(height, width, starty, startx);

  //attron(COLOR_PAIR(1));
	box(local_win, 0, 0);
  //attroff(COLOR_PAIR(1));

	wrefresh(local_win);
	return local_win;
}

void destroy_win(WINDOW* local_win){
	wborder(local_win,' ',' ',' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	delwin(local_win);
}

bool ui_comp(const Gameobject* a, const Gameobject* b){
  return (a->get_depth()) < (b->get_depth());
}

void ui_print(Map* whole_map, WINDOW* gamebox){
	//TODO WHOLE MAP MUST BE CONST!!!
	werase(gamebox);
	Player * p = whole_map->get_player();
	int off_x = 30-p->_px; //(10,30) (y,x) is currently the middle
	int off_y = 10-p->_py;

	std::sort(whole_map->get_gameobj()->begin(), whole_map->get_gameobj()->end(), ui_comp);
	//Fixa depth
	for(auto i = whole_map->get_gameobj()->begin(); i != whole_map->get_gameobj()->end(); ++i){
		int print_x = (*i)->_px + off_x;
		int print_y = (*i)->_py + off_y;
		if(print_x>-1 || print_y>-1){
			mvwprintw(gamebox, print_y, print_x, "%c", (*i)->get_img());
		}
		
		char icon = (*i)->get_img();
	}
	box(gamebox, 0, 0);
	wrefresh(gamebox);
	//std::cout << "... apparently :)" << std::endl;
}

//Prints the players inventory in the right window
//TODO only sholw the first x items, not scrollable/controlable
//idealy we could swhitch to inv wing makr a ex. potion and press enter to use
void inv_print(Player * p, WINDOW* inventbox){
  werase(inventbox);
  
  //attron(bold); bold is wrong.. :(
  mvwprintw(inventbox, 1,1 ,"    Inventory");
  //attroff(bold);
  //TODO remove hårdkoding
  for(int i = 2; i<20; ++i){
    mvwprintw(inventbox,i,1,"~");
  }

  int j = 2;
  for(auto i = p->get_inventory()->begin(); i != p->get_inventory()->end(); ++i){
    std::string name = (**i)._name;
    mvwprintw(inventbox,j,2,"%s",name.c_str());
    ++j;
  }

  box(inventbox, 0, 0);
  wrefresh(inventbox);
}
int main(){
  //Load necessities

  //Setting up 3+1 windows, should be more..
  WINDOW* game_win;
	WINDOW* inv_win;
	WINDOW* text_win;

	int gstartx,gstarty,gheight,gwidth;
	int istartx,istarty,iheight,iwidth;
	int tstartx,tstarty,theight,twidth;
	int ch;

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
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

	game_win = create_newwin(gheight, gwidth, gstarty, gstartx);
	inv_win = create_newwin(iheight, iwidth, istarty, istartx);
	text_win = create_newwin(theight, twidth, tstarty, tstartx);
	WINDOW* scroll_win = newwin(2,78,21,1);
  scrollok(scroll_win, TRUE);
	getch();
	Map themap("maps/map2.txt", scroll_win);
	ui_print(&themap, game_win);
  
    //Move
    while((ch=getch()) != KEY_F(2)){
    	int dx = 0;
    	int dy = 0;
    	switch(ch){
    		case KEY_LEFT:
    			dx = -1;
    			break;

    		case KEY_RIGHT:
    			dx = 1;
    			break;

    		case KEY_UP:
    			dy = -1;
    			break;

    		case KEY_DOWN:
    			dy = 1;
    			break;

        case '\t':
          //Use tab to control ther windown in the ui maybe, welp
          mvwprintw(inv_win,3,1,"Got tab");
          wrefresh(inv_win);
          break;
    	}



    int newx = themap.get_player()->_px + dx;
    int newy = themap.get_player()->_py + dy;

    //Players turn
    //Checks is wanted position is non-solid
    if(themap.is_free(newx, newy)){
      themap.get_player()->move(dx, dy);//->_px = newx;
    }else if(themap.enemy_exists(newx, newy)){ //If an enemy exists on that position
      Enemy * newenemy = themap.get_enemy(newx, newy);
      themap.get_player()->attack(*newenemy); //Tell player to attack it, attack defined in actor
    }else if(themap.structure_exists(newx, newy)){
      themap.get_player()->interact(themap.get_structure(newx, newy));
    }
    themap.cleanup();
    if(themap.get_player()->has_won()){
      break;
    }
    ui_print(&themap, game_win);
    inv_print(themap.get_player(), inv_win);
    //Enemies turn
    std::vector<Enemy *> enemies = themap.get_enemies();
    for(auto i = enemies.begin(); i != enemies.end(); ++i){
      if((**i).may_act()){
        //1. Is there anything around me I can attack?
        if((**i).is_near_me(*themap.get_player())){
          (**i).attack(*themap.get_player());
        }
        //2. If not, chase the player
        else{
        themap.find_path((**i), *themap.get_player());

        }
      }
      themap.cleanup();
    }

    //Update camera and print

    ui_print(&themap, game_win);
  	}

  if(themap.get_player()->has_won()){
    //You won
  }else{
    //You lost
  }
  delwin(game_win);
  delwin(inv_win);
  delwin(text_win);
  delwin(scroll_win);
  endwin();
}
	
