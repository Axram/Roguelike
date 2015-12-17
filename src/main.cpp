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
  Map themap("maps/map1.txt"); //Load map
  Camera m(50, 50, 0, 0); //Create camera
  Textbox textbox(0, 40, 50, 10); //px, py, sizex, sizey
  //Prepare first print
  m.centralize(themap.get_player()); 
  m.add_gameobjects(themap.get_map());
  m.print();

  while(1){
    
    //get input
    std::string s;
    getline(std::cin,s);
  
    //Move
    int dx = 0;
    int dy = 0;
    
    if(s == "up" || s =="\33[A" || s == "w") dy = -1;
    if(s == "down" || s == "\33[B" || s == "s") dy = 1;
    if(s == "right" || s == "\33[C" || s == "d") dx = 1;
    if(s == "left" || s == "\33[D" || s == "a") dx = -1;
    int newx = themap.get_player()._px + dx;
    int newy = themap.get_player()._py + dy;
    if(themap.is_free(newx, newy)){
      themap.get_player()._px = newx;
      themap.get_player()._py = newy;
      textbox.add_row("You move");
    }else if(themap.enemy_exists(newx, newy)){ //If an enemy exists on that position
      Enemy * newenemy = themap.get_enemy(newx, newy);
      textbox.add_row("You attack something");
      bool killed = themap.get_player().attack(*newenemy); //Tell player to attack it, attack defined in actor
      if(killed){
        textbox.add_row("You killed something");
        (*newenemy).die();
        //Delete the eenmie from the map vectors
        //themap._go.erase(newenemy);
      }
    }
    //Update camera and print
    themap.cleanup();
    m.centralize(themap.get_player());
    m.add_gameobjects(themap.get_map());
    m.print();
    textbox.print();
  }
}
	
