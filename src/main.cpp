#include "gameobject.hpp"
#include "wall.hpp"
#include "player.hpp"
#include "map.hpp"
#include "goblin.hpp"
#include "ui.hpp"

#include <ncurses.h>
#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <stdlib.h> 


void introduction(){
  erase();
  printw("\"Who dares to enter THE GATES OF XOR?\"\n");
  printw("...\n");
  printw("\"An adventurer I see. Hmm... I might have use for you.\n");
  printw("Find the long lost Chalice of Doom and bring it to the Altar of Doom\n");
  printw("If you accomplish this I will be merciful, else{}...\"\n\n");
  printw("\n");
  printw("\n(Move with arrow keys, exit with F2, save with F5, load with F9)\n");
  printw("\nPress ANY key to continue");
  int ch;
  ch = getch();
  ch = ch; //To remove that pesky warning
}
void good_ending(){
  erase();
  printw("\"CONGRATULATIONS you have won the game\"");
  printw("\n");
  printw("\"Well done my adventurer, you have proven to be worthy.\n");
  printw("Found the long lost Chalice of Doom \n");
  printw("I am good hearted and will now relieve you of your burden. Good Bye\"\n\n");
  printw("\n\n");
  printw("\nPress ENTER key to exit the game");
  while(getch() != 10){}
}

void bad_ending(){
  erase();
  printw("\"YOU DIED\"");
  printw("\n");
  printw("\nTry being less crap next time. \n");
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
          if(choose_state == 0){

            introduction();
            endwin();
            return "testmap";

          }else if(choose_state == 1){
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
  return "secretlegacy"; //OOEOOEOO
}

int main(){
  std::string load_filename = main_menu();

  //##### Load necessities #####
  Ui * ui = new Ui();
  /* Code reference
  std::map<std::string, bool (Gameobject::*) (Gameobject &)> funkpoint;
  funkpoint["near me"] = &Gameobject::is_near_me;
  */
  Map * themap = new Map(load_filename, ui->_scroll_win);
  /*
  Gameobject p;
  bool h = (p.*funkpoint["near me"])(p);
  */
  ui->ui_print(themap);
  bool victory_achieved = false;


  //##### Get keyinputs #####
  int ch;
    while((ch=getch()) != KEY_F(2)){
    	int dx = 0;
    	int dy = 0;
        //Movement
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
        case 104:
          themap->get_player()->heal(10);
          break;
        case KEY_F(5): //Save
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
          themap->save_data_new(yourname);
          cbreak();
          curs_set(0);
          noecho();
          break;
        }
        case KEY_F(9): //Load
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
          mvwprintw(ui->_inv_win,3,1,"Got tab");
          wrefresh(ui->_inv_win);
          break;
    	}



    int newx = themap->get_player()->_px + dx;
    int newy = themap->get_player()->_py + dy;

    //##### Players turn #####

    if(themap->enemy_exists(newx, newy)){
      Enemy * newenemy = themap->get_enemy(newx, newy);
      themap->get_player()->attack(*newenemy);
    }else if(themap->is_free(newx, newy)){
      themap->get_player()->move(dx, dy);
    }else if(themap->structure_exists(newx, newy)){
      themap->get_player()->interact(themap->get_structure(newx, newy));
    }
   themap->cleanup();

    //Check for player victory.

   if(themap->get_player()->has_won()){
     victory_achieved = true;
     break;
   }

    //##### Enemies turn #####
    std::vector<Enemy *> enemies = themap->get_enemies();
    for(auto i = enemies.begin(); i != enemies.end(); ++i){
      if((**i).may_act()){
        bool action_taken = false;
        if((**i).is_near_me(*themap->get_player())){
          (**i).attack(*themap->get_player());
          continue;
        }
        for(auto npc = themap->get_npcs()->begin(); npc != themap->get_npcs()->end(); ++npc){
            if((**i).is_near_me(**npc)){
              (**i).attack(**npc);
              action_taken = true;
              break;
            }
        }
        if(!action_taken){
          themap->find_path((**i), *themap->get_player());
        }
      }
      if(themap->get_player()->get_to_be_removed())break;
      themap->cleanup();
    }
    if(themap->get_player()->get_to_be_removed())break;
    
    //##### NPCs turn #####
    int npc_dx[4] = {0,0,1,-1}; //North, south, east, west
    int npc_dy[4] = {1,-1,0,0};
    std::vector<Npc*> * npcs = themap->get_npcs();
    for(auto i = npcs->begin(); i != npcs->end(); ++i){
      if((**i).may_act()){
        if((**i).is_roaming()){
          int numb = rand()%4;
          int newx = (**i)._px + npc_dx[numb];
          int newy = (**i)._py + npc_dy[numb];
          if(themap->is_free(newx, newy)){
            (**i).move(npc_dx[numb], npc_dy[numb]);
          } 
        }
      }
    }
    //Update camera and print
    ui->ui_print(themap);//, game_win);
    ui->inv_print(themap->get_player());
  	}
    //##### Post game #####

  std::string lol = "Press enter to continue";
  scroll(ui->_scroll_win);
  mvwprintw(ui->_scroll_win,1,1,"%s", lol.c_str());
  wrefresh(ui->_scroll_win);
  delete themap;

  while(getch() != 10){}
  delete ui;
  
  initscr();
  cbreak();       //Read one char at the time
  noecho();       //Pressed button in not shown
  keypad(stdscr, TRUE); //Enables the keyboard
  curs_set(0);
  //Gets enter to continue
  
  if(victory_achieved){
    good_ending();
  }else{
    bad_ending();
  }
  endwin();

}
	
