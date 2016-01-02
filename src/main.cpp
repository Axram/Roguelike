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
#include <cassert>


void introduction(){
  erase();
  printw("\"Who dares to enter THE GATES OF XOR\"");
  printw("\n");
  printw("\n(Move with arrow keys, exit with F2, save with F5, load with F9)\n");
  printw("\nPress ANY key to continue");
  int ch;
  ch = getch();
}
void good_ending(){
  erase();
  printw("\"CONGRATULATIONS you have opened THE GATES OF XOR\"");
  printw("\n");
  printw("\n\n");
  printw("\nPress ENTER key to exit the game");
  while(getch() != 10){}
}

void bad_ending(){
  erase();
  printw("\"YOU DIED\"");
  printw("\n");
  printw("\nTry being less crap next time \n");
  printw("\nPress ENTER key to exit the game");
  while(getch() != 10){}
}

std::string main_menu(void){
  //Make a main menu where you choose new game or load game from file, maybe?
  initscr();
  cbreak();       //Read one char at the time
  noecho();       //Pressed button in not shown
  keypad(stdscr, TRUE); //Enables the keyboard
  curs_set(0);
  
  printw("THE MIGHTY CRUSADE \n");
  printw(">NEW GAME \n");
  printw(" LOAD GAME \n");
  int choose_state = 0;
  int ch;
  while((ch=getch()) != KEY_F(2)){
      switch(ch){
        case KEY_DOWN:
          choose_state = 1;
          mvprintw(1,0," ");
          mvprintw(2,0,">");
          break;
        
        case KEY_UP:
          choose_state = 0;
          mvprintw(1,0,">");
          mvprintw(2,0," ");

          break;

        case 10:
            //assert(false);
          if(choose_state == 0){

            introduction();
            endwin();
            return "map2";

          }else if(choose_state = 1){
            curs_set(1);
            echo();
            raw(); 
            refresh();
            std::string str = "maps/";
            std::string ext = ".savegame";
            char in[100];
            while(true){
              printw("\nEnter name of save\n");
              getstr(in);
              
              std::string fname = in;
              std::string filename = str+fname+ext;
              //Check if valid filename
              if(FILE *file = fopen(filename.c_str(),"r")){
                fclose(file);
                erase();
                refresh();
                endwin();
                return fname;
              }
              printw("FILE DOES NOT EXIST, TRY AGAIN\n");
            }
          }
          break;
      }
    
  }
  endwin();
  return "map2";
}

int main(){
  std::string load_filename = main_menu();
  //std::cout << strhd << strhd.length() <<std::endl;
  //assert(false);
  //Load necessities
  Ui * ui = new Ui();
  //Ui ui;
  int ch;
	//getch(); // Press enter to start the game
  std::map<std::string, bool (Gameobject::*) (Gameobject &)> funkpoint;
  funkpoint["near me"] = &Gameobject::is_near_me;

	//Map themap("maps/map2.txt", ui->_scroll_win);
  //Map themap(load_filename, ui->_scroll_win);
  Map * themap = new Map(load_filename, ui->_scroll_win);
  Gameobject p;
  bool h = (p.*funkpoint["near me"])(p);
	//ui_print(&themap, game_win);
  ui->ui_print(themap);
  bool victory_achieved = false;
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
        
        case KEY_F(5):
        {
          raw();
          curs_set(1);
          echo();
          char in[100];
          scroll(ui->_scroll_win);
          mvwprintw(ui->_scroll_win,1,1,"Enter name of save: ");
          wrefresh(ui->_scroll_win);
          wgetstr(ui->_scroll_win,in);
          std::string yourname = in;
          themap->save_data(yourname);
          cbreak();
          curs_set(0);
          noecho();
          break;
        }
        case KEY_F(9):
        {
          delete themap;
          raw();
          curs_set(1);
          echo();
          char in[100];
          std::string yourname;
          while(true){
            scroll(ui->_scroll_win);
            mvwprintw(ui->_scroll_win,1,1,"Enter name of file to load: ");
            wrefresh(ui->_scroll_win);
            wgetstr(ui->_scroll_win,in);
            yourname = in;
            if(FILE *file = fopen(("maps/"+yourname +".savegame").c_str(),"r")){
              fclose(file);
              break;
            }
          }
          cbreak();
          curs_set(0);
          noecho();
          themap = new Map(yourname, ui->_scroll_win);
          break;
        }
        case '\t':
          //Use tab to control ther windown in the ui maybe, welp
          mvwprintw(ui->_inv_win,3,1,"Got tab");
          wrefresh(ui->_inv_win);
          break;
    	}



    int newx = themap->get_player()->_px + dx;
    int newy = themap->get_player()->_py + dy;

    //Players turn
    //Checks is wanted position is non-solid
    if(themap->is_free(newx, newy)){
      themap->get_player()->move(dx, dy);//->_px = newx;
    }else if(themap->enemy_exists(newx, newy)){ //If an enemy exists on that position
      Enemy * newenemy = themap->get_enemy(newx, newy);
      themap->get_player()->attack(*newenemy); //Tell player to attack it, attack defined in actor
    }else if(themap->structure_exists(newx, newy)){
      themap->get_player()->interact(themap->get_structure(newx, newy));
    }
   
   themap->cleanup();

    //Check for player victory.
    std::vector<Item*> * inv = themap->get_player()->get_inventory();
    for(auto i = inv->begin(); i != inv->end(); ++i){
      if((**i)._name == "WINITEM"){
        victory_achieved = true;
        break;
      }
    }
    if(victory_achieved) break;

    ui->ui_print(themap);
    ui->inv_print(themap->get_player());

    //Enemies turn
    std::vector<Enemy *> enemies = themap->get_enemies();
    for(auto i = enemies.begin(); i != enemies.end(); ++i){
      if((**i).may_act()){
        //1. Is there anything around me I can attack?
        if((**i).is_near_me(*themap->get_player())){
          (**i).attack(*themap->get_player());
        }
        //2. If not, chase the player
        else{
          themap->find_path((**i), *themap->get_player());
        }
      }
      if(themap->get_player()->get_to_be_removed())break;//Player loss
      themap->cleanup();
    }
    if(themap->get_player()->get_to_be_removed())break;
    
    //Update camera and print
    ui->ui_print(themap);//, game_win);
  	}
    
  while(getch() != 10){}
  delete themap;
  delete ui;
  
  initscr();
  cbreak();       //Read one char at the time
  noecho();       //Pressed button in not shown
  keypad(stdscr, TRUE); //Enables the keyboard
  curs_set(0);
  if(victory_achieved){
    good_ending();
  }else{
    bad_ending();
  }
  endwin();

}
	
