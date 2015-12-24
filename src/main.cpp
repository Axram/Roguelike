#include "gameobject.hpp"
#include "camera.hpp"
#include "wall.hpp"
#include "functions.cpp"
#include "player.hpp"
#include "map.hpp"
#include "goblin.hpp"
#include "textbox.hpp"
#include "ui.hpp"

#include <ncurses.h>

#include <vector>
#include <string>
#include <iostream>

/*
std::string main_menu(void){
  //Make a main menu where yoy choose new game or load game from file, maybe?
  
*/
Ui * ui = new Ui(); //TODO make not GLOBAL...
void text_control(); //Forward declare for now
void inv_control(Player * p){
//After tab is pressed you end up here.
//Supposed to display desctiptions of carried items
	int ch;
	while((ch=getch()) != KEY_F(2)){
		switch(ch){
    		case '\t':
    			text_control();
    			return;
    			break;
    	}
	}

}
void text_control(){
//After tab+tab is pressed you end yp here.
//Was supposed to scroll among olt log entries
	int ch;
	while((ch=getch()) != KEY_F(2)){
		switch(ch){
    		case KEY_UP:
    			scroll(ui->_scroll_win);
    			wrefresh(ui->_scroll_win);
    			break;

    		case KEY_DOWN:
    			wscrl(ui->_scroll_win, -1);
    			wrefresh(ui->_scroll_win);
    			break;

	        case '\t':
	        	//Goto menu win
	        	return;
	        	break;

	        case KEY_BTAB:
	        	//Goto inv window
	        	return;
	        	break;
    	}
	}

}
void menu_control(){
	int ch;
	while((ch=getch()) != KEY_F(2)){
		switch(ch){
			case KEY_ENTER:
				//Well?
				//quit = true;
				break;
    		case '\t':
    			text_control();
    			return;
    			break;
    	}
	}
}
int main(){
  //Load necessities
  //Ui * ui = new Ui();//kanske lägga allt på heapen ist
  //Ui ui;
  int ch;
	getch(); // Press enter to start the game

	Map themap("maps/map2.txt", ui->_scroll_win);
	//ui_print(&themap, game_win);
  ui->ui_print(&themap);
  bool quit = false;
    //Move
    while((ch=getch()) != KEY_F(2) && !quit){
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
	          inv_control(themap.get_player());
	          /*
	          mvwprintw(ui->_inv_win,3,1,"Got tab");
	          wrefresh(ui->_inv_win);
	          */
	          break;

	        case KEY_BTAB:
	        	//Goto menu window
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
    ui->ui_print(&themap);//, ui._game_win);
    ui->inv_print(themap.get_player());//, ui._inv_win);
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

    ui->ui_print(&themap);//, game_win);
  	}

  if(themap.get_player()->has_won()){
    //You won
  }else{
    //You lost
  }

  delete ui;
}
	
