#include "gameobject.hpp"
#include "map.hpp"
#include "wall.hpp"
#include "functions.cpp"
#include <vector>
#include <iostream>
int main(){
  std::vector<Gameobject> go;
  for(int y = -100; y < 100; ++y){
  	for(int x = -100; x < 100; ++x ){
  		if(x == 0){
  			Wall w(x,y);
  			go.push_back(w);
  		}
  	}
  }
  //Gameobject g;
  //Wall w(5, 5);
  //go.push_back(g);
  //go.push_back(w);
  Map m(40, 40, 0, 0);
  
  while(1){
  	std::string s;  
  	m.add_gameobjects(go);
  	m.print();
  	getline(std::cin,s);
  	if(s == "up") m._top_y +=1;
  	if(s == "down") m._top_y -=1;
  	if(s == "right") m._top_x +=1;
  	if(s == "left") m._top_y -=1;
  	m.calculate_boundaries();
  }
}
	