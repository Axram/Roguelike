#include "gameobject.hpp"
#include "camera.hpp"
#include "wall.hpp"
#include "functions.cpp"
#include "player.hpp"
#include "map.hpp"
#include <vector>
#include <iostream>
int main(){
  /*
    std::vector<Gameobject*> go;
    for(int y = -100; y < 100; ++y){
    for(int x = -100; x < 100; ++x ){
    if(x == 10 || x == 30 || y == 5 || y == 20){
    Wall * w =  new Wall(x,y);
    go.push_back(w);
    }
    }
    }
  */
  Map themap("maps/map1.txt");
  //Gameobject g;
  //Wall w(5, 5);
  //go.push_back(g);
  //go.push_back(w);
  Camera m(50, 50, 0, 0);
  //m.centralize(p);
  //nope
  m.centralize(themap.get_player());
  m.add_gameobjects(themap.get_map());
  //m.print();
  while(1){
    std::string s;
    getline(std::cin,s);
    //std::cout << p->_py << std::endl;
    if(s == "up" || s =="\33[A" || s == "w") themap.get_player()._py -=1;
    if(s == "down" || s == "\33[B" || s == "s") themap.get_player()._py +=1;
    if(s == "right" || s == "\33[C" || s == "d") themap.get_player()._px +=1;
    if(s == "left" || s == "\33[D" || s == "a") themap.get_player()._px -=1;
    m.centralize(themap.get_player());
    //std::cout << (themap.get_map()[1]->_px) << std::endl
    m.add_gameobjects(themap.get_map());
    //m.print();
  }
}
	
