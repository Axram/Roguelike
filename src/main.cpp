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
int main(){
  //Load necessities
  Ui * ui = new Ui();//kanske lägga allt på heapen ist
  //Ui ui;
  int ch;
	getch(); // Press enter to start the game

	Map themap("maps/map2.txt", ui->_scroll_win);
	//ui_print(&themap, game_win);
  ui->ui_print(&themap);
  
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
          mvwprintw(ui->_inv_win,3,1,"Got tab");
          wrefresh(ui->_inv_win);
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
	
