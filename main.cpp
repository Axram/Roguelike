#include "gameobject.hpp"
#include "camera.hpp"
#include "wall.hpp"
#include "functions.cpp"
#include "player.hpp"
#include <vector>
#include <iostream>
int main(){
  std::vector<Gameobject*> go;
  for(int y = -100; y < 100; ++y){
  	for(int x = -100; x < 100; ++x ){
  		if(x == 10 || x == 30 || y == 5 || y == 20){
  			Wall * w =  new Wall(x,y);
  			go.push_back(w);
  		}
  	}
  }
  //Gameobject g;
  //Wall w(5, 5);
  //go.push_back(g);
  //go.push_back(w);
  Player p(10,10);
  go.push_back(&p);
  Camera m(40, 40, 0, 0);
  m.centralize(p);
  
  while(1){
  	std::string s;
    getline(std::cin,s);
    if(s == "up" || s =="\33[A") p._py -=1;
    if(s == "down" || s == "\33[B") p._py +=1;
    if(s == "right" || s == "\33[C") p._px +=1;
    if(s == "left" || s == "\33[D") p._px -=1;
    m.centralize(p);
  	m.add_gameobjects(go);

  	m.print();

    
  	
  }
}
	