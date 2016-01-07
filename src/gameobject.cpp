
#include <string>
#include "gameobject.hpp"

Gameobject::Gameobject(){}

void Gameobject::set_vars(std::string type, 
	int px, 
	int py, 
	int depth, 
	std::string name, 
	std::string desc, 
	char img, bool solid, 
	bool movable,
	WINDOW * text){
_type =type; 
_px = px; 
_py = py; 
_depth=depth; 
_name=name; 
_desc=desc; 
_img=img; 
_solid=solid; 
_movable=movable;
_textbox = text;
}

Gameobject::~Gameobject(){}
bool Gameobject::operator<(const Gameobject & b){
  return _depth < b._depth;

}

bool Gameobject::get_to_be_removed()const{
  return _to_be_removed;
}
char Gameobject::get_img()const{
  return _img;
}
int Gameobject::get_depth()const{
  return _depth;
}
bool Gameobject::get_solid()const{
  return _solid;
}
std::string Gameobject::get_name()const{
	return _name;
}
std::string Gameobject::get_desc()const{
	return _desc;
}
bool Gameobject::is_near_me(Gameobject & other){
	//NSEW 
	int dx[4] = {0,0,1,-1};
	int dy[4] = {1,-1,0,0};
	for(int i = 0; i < 4; ++i){
		if(other._px == _px + dx[i] && other._py == _py + dy[i]) return true;
	}
	return false;
}
void Gameobject::remove(){
  _to_be_removed =true;
}
std::string Gameobject::get_data(){
	std::string return_data;
	return_data += _name+'\n';
	return_data += std::to_string(_px)+'\n';
	return_data += std::to_string(_py)+'\n';
	return return_data;
	//return_data += _depth+'\n';
	//return_data += _solid+'\n';
	//return_data += _movable+'\n';
	//return_data += _img+'\n';
	//return_data += _desc+'\n';

}

std::string Gameobject::get_data_new(){
	std::string s;
	s+= _type+'\n';
	s+= std::to_string(_px) + '\n';
	s+= std::to_string(_py) + '\n';
	s+= std::to_string(_depth) + '\n';
	s+= _name+'\n';
	s+= _desc+'\n';
	s+= _img;
	s+= '\n';
	_solid == true ? s+="True\n" : s+= "False\n";
	_movable == true ? s+= "True\n" : s+= "False\n";
	return s; 
}