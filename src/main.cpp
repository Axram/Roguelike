#include "gameobject.hpp"
#include "camera.hpp"
#include "wall.hpp"
#include "functions.cpp"
#include "player.hpp"
#include "map.hpp"
#include "goblin.hpp"
#include "textbox.hpp"
#include <vector>
#include <iostream>

std::string main_menu(void){
  //Make a main menu where yoy choose new game or load game from file, maybe?
}

int main(){
  //Load necessities

  Camera m(50, 30, 5, 5); //Create camera
  Textbox * textbox = new Textbox(0, 40, 50, 9); //px, py, sizex, sizey
  Map themap("maps/map2.txt", textbox); //Load map
  //Prepare first print
  m.centralize(*themap.get_player()); 
  m.add_gameobjects(themap.get_map());
  m.print();

  while(1){
    
    //get input
    std::string s;
    getline(std::cin,s);
  
    //Move
    int dx = 0;
    int dy = 0;

    //TODO, check if word is use
    if(s.find("use") != std::string::npos){
      //textbox.add_row("Attempts to use");
    }
    
    if(s == "up" || s =="\33[A" || s == "w") dy = -1;
    if(s == "down" || s == "\33[B" || s == "s") dy = 1;
    if(s == "right" || s == "\33[C" || s == "d") dx = 1;
    if(s == "left" || s == "\33[D" || s == "a") dx = -1;
    int newx = themap.get_player()->_px + dx;
    int newy = themap.get_player()->_py + dy;
    //Checks is wanted position is non-solid
    if(themap.is_free(newx, newy)){
      themap.get_player()->move(dx, dy);//->_px = newx;
      //themap.get_player()->_py = newy;
      //textbox.add_row("You move");
    }else if(themap.enemy_exists(newx, newy)){ //If an enemy exists on that position
      Enemy * newenemy = themap.get_enemy(newx, newy);
      //textbox.add_row("You attack something");
      bool killed = themap.get_player()->attack(*newenemy); //Tell player to attack it, attack defined in actor
      if(killed){
        //textbox.add_row("You killed something");
       
      }
    }else if(themap.structure_exists(newx, newy)){
      //Structure * newst = themap.get_structure(newx, newy);
      //textbox.add_row("You interact with the structure");
      themap.get_player()->interact(themap.get_structure(newx, newy));
      //bool didit = newst->interact((themap.get_player())->get_inventory());
    }
    std::vector<Enemy *> enemies = themap.get_enemies();
    for(auto i = enemies.begin(); i != enemies.end(); ++i){
      if((**i).may_act()){
        //1. Is there anything around me I can attack?
        if((**i).is_near_me(*themap.get_player())){
          (**i).attack(*themap.get_player());
        }
        else{

        themap.find_path((**i), *themap.get_player());
          
        }
        //2. If not, chase the player
      }
    }
    //Enemies trun to move??

    //Update camera and print
    themap.cleanup();
    m.centralize(*themap.get_player());
    m.add_gameobjects(themap.get_map());
    m.print();
    textbox->print();
  }
  delete textbox;
}
	
