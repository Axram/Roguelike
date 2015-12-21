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
	box(local_win, 0, 0);
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
	//mvwprintw(gamebox,1,1,"Whats is going on");
	//std::cout << "Did i do anything?" << std::endl;
	//TODO make py, py private and call get pos routinte instead
	int off_x = 30-p->_px; //(10,30) (y,x) is currently the middle
	int off_y = 10-p->_py;

	std::sort(whole_map->get_gameobj()->begin(), whole_map->get_gameobj()->end(), ui_comp);
	//Fixa depth
	for(auto i = whole_map->get_gameobj()->begin(); i != whole_map->get_gameobj()->end(); ++i){
		int print_x = (*i)->_px + off_x;
		int print_y = (*i)->_py + off_y;
		//std::string icon = (*i)->get_img();
		//std::cout << "i" << std::endl;
		//mvwprintw(gamebox, print_y, print_x, "%s", icon.c_str());
		if(print_x>-1 || print_y>-1){
			mvwprintw(gamebox, print_y, print_x, "%c", (*i)->get_img());
		}
		
		char icon = (*i)->get_img();
	}
	box(gamebox, 0, 0);
	wrefresh(gamebox);
	//std::cout << "... apparently :)" << std::endl;
}

int main(){
  //Load necessities

  //Camera m(50, 30, 5, 5); //Create camera
  //Textbox * textbox = new Textbox(0, 40, 50, 9); //px, py, sizex, sizey
  //Map themap("maps/map2.txt", textbox); //Load map
  //Prepare first print
  //m.centralize(*themap.get_player()); 
  //m.add_gameobjects(themap.get_map());
  //m.print();

  //while(1){
    //Setting up 4 windows, should be more..
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
	refresh(); // APperently very important
	game_win = create_newwin(gheight, gwidth, gstarty, gstartx);
	inv_win = create_newwin(iheight, iwidth, istarty, istartx);
	text_win = create_newwin(theight, twidth, tstarty, tstartx);
	WINDOW* scroll_win = newwin(2,78,21,1);
	getch();
	//endwin();
	//return 0;
	scrollok(scroll_win, TRUE);
	Map themap("maps/map2.txt", scroll_win);
	ui_print(&themap, game_win);
	//std::cout << "Made it here" << std::endl;
  
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
    	}
/*
    //TODO, check if word is use
    if(s.find("use") != std::string::npos){
      //textbox.add_row("Attempts to use");
    }
    
    if(s == "up" || s =="\33[A" || s == "w") dy = -1;
    if(s == "down" || s == "\33[B" || s == "s") dy = 1;
    if(s == "right" || s == "\33[C" || s == "d") dx = 1;
    if(s == "left" || s == "\33[D" || s == "a") dx = -1;
*/


    int newx = themap.get_player()->_px + dx;
    int newy = themap.get_player()->_py + dy;

    //Segfault here...
    //bool men =themap.is_free(newx, newy);
    
    //Checks is wanted position is non-solid
    if(themap.is_free(newx, newy)){
      themap.get_player()->move(dx, dy);//->_px = newx;
    }else if(themap.enemy_exists(newx, newy)){ //If an enemy exists on that position
      Enemy * newenemy = themap.get_enemy(newx, newy);
      themap.get_player()->attack(*newenemy); //Tell player to attack it, attack defined in actor
    }else if(themap.structure_exists(newx, newy)){
      themap.get_player()->interact(themap.get_structure(newx, newy));
    }
    
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
      
    }

    //Update camera and print
    //themap.cleanup();

    ui_print(&themap, game_win);
    /*
    m.centralize(*themap.get_player());
    m.add_gameobjects(themap.get_map());
    m.print();
    textbox->print();
    */
  	}
  //} is friend with while(1)
  //delete textbox;
  endwin();
}
	
