#include "camera.hpp"
#include "functions.cpp"
#include <stdexcept>
#include <iostream>
#include <string>
#include <typeinfo>
Camera::Camera(int sizex, int sizey, int posx, int posy){
  _size_x = sizex;
  _size_y = sizey;
  _pos_x = posx;
  _pos_y = posy;

  calculate_boundaries();
  std::vector<char> c;
  c.resize(_size_x, ' '); //This -1 might cause trouble
  for(int i = 0; i < _size_y; ++i){
  	_grid.push_back(c);
  }
}

void Camera::calculate_boundaries(){ //Calculates which positions should be shown on the Camera
	//Where is the pos?
	//Which px is on the borders?
	_min_x = _pos_x;
	_max_x = _pos_x+_size_x;
	_min_y = _pos_y;
	_max_y = _pos_y+_size_y;
}
void Camera::centralize(const Gameobject & g){
	int px = g._px;
	int py = g._py;
	_pos_x = px-_size_x/2;
	_pos_y = py-_size_y/2;
}
void Camera::add_gameobjects(std::vector<Gameobject> & g){ //Segfault central
	calculate_boundaries();
  for(auto i = g.begin(); i != g.end(); ++i){
  	if(i->_px < _min_x || i-> _px >= _max_x) continue; // If it's not relevant skip it
  	if(i->_py < _min_y || i-> _py >= _max_y) continue;
  	int x = i->_px - _pos_x; // calculate the correct position on the grid
  	int y = i->_py - _pos_y;
  	_grid[y][x] = i->_img;
    //If px and py on Camera. Add onto grid at correct position
    
  }
  
}
void Camera::add_gameobjects(std::vector<Gameobject*> & g){ //Segfault central
	
	calculate_boundaries();
  for(auto i = g.begin(); i != g.end(); ++i){
  	Gameobject* j = *i;
  	std::cout << typeid(j).name() << '\n';

  	//Gameobject j = *i;
  	if(j->_px < _min_x || j-> _px >= _max_x) continue; // If it's not relevant skip it
  	if(j->_py < _min_y || j-> _py >= _max_y) continue;
  	int x = j->_px - _pos_x; // calculate the correct position on the grid
  	int y = j->_py - _pos_y;
  	std::cout << "x " << x << std::endl;
  	_grid[y][x] = j->_img;
  	std::cout <<"helo" << std::endl;
   //  //If px and py on Camera. Add onto grid at correct position
    
  }
  
}
void Camera::set_cursor(int px, int py)const{ //set cursor on terminal
	++px;
	++py;
	std::cout << "\33[" << px << ";" << py << "H"; 
}
void Camera::clear_screen()const{ //clear the screen through magic
	std::cout << "\33[2J";
}
void Camera::clear_grid(){
	for(int y = 0; y < _grid.size(); ++y){
		for(int x = 0; x < _grid[y].size(); ++x){
			_grid[y][x] = ' ';
		}
	}
}
void Camera::print(){   //Print out the grid on to the terminal

	clear_screen();
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
	clear_grid();
}
