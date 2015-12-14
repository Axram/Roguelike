#include "map.hpp"
#include "functions.cpp"
#include <stdexcept>
#include <iostream>
#include <string>
Map::Map(int sizex, int sizey, int topx, int topy){
  _size_x = sizex;
  //if(_size_x%2 == 0) _size_x+=1; //Avoid even numbers
  //if(_size_y%2 == 0) _size_y+=1;
  _size_y = sizey;
  _top_x = topx;
  _top_y = topy;

  calculate_boundaries();
  std::vector<char> c;
  c.resize(_size_x, ' '); //This -1 might cause trouble
  for(int i = 0; i < _size_y; ++i){
  	_grid.push_back(c);
  }
}

void Map::calculate_boundaries(){ //Calculates which positions should be shown on the map
	//Where is the top?
	//Which px is on the borders?
	_min_x = _top_x;
	_max_x = _top_x+_size_x;
	_min_y = _top_y;
	_max_y = _top_y+_size_y;
	

}

void Map::add_gameobjects(std::vector<Gameobject> & g){ //Segfault central
  for(auto i = g.begin(); i != g.end(); ++i){
  	if(i->_px < _min_x || i-> _px >= _max_x) continue; // If it's not relevant skip it
  	if(i->_py < _min_y || i-> _py >= _max_y) continue;
  	int x = i->_px + _top_x; // calculate the correct position on the grid
  	int y = i->_py + _top_y;
  	_grid[y][x] = i->_img;
    //If px and py on map. Add onto grid at correct position
    
  }
  
}
void Map::set_cursor(int px, int py){ //set cursor on terminal
	++px;
	++py;
	std::cout << "\33[" << px << ";" << py << "H"; 
}
void Map::clear_screen(){ //clear the screen through magic
	std::cout << "\33[2J";
}
void Map::print(){   //Print out the grid on to the terminal

	//clear_screen();
	set_cursor(0,0);
	std::string s;
	for(int y = 0; y < _grid.size(); ++y){
		for(int x = 0; x < _grid[y].size(); ++x){
			s+= _grid[y][x];
		}
	s += '\n';
	}
	s.pop_back(); //remove the last linebreak
	std::cout << s; //It's generally more effective to just print once. 

}
