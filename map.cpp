#include "map.hpp"
Map::Map(int sizex, int sizey, int centre){
  //TODO generate map
  _sizex = sizex;
  _sizey = sizey;
  _centre = centre;
}

Map::add_gameobjects(std::vector<Gameobject> & g){
  for(auto i = g.begin(); i != g.end(); ++g){
    //If px and py on map. Add onto grid at correct position
    
  }
  
}

Map::print(){
  //Print out the grid on to the terminal
}
