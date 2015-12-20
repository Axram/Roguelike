
#include <string>
#include "gameobject.hpp"

Gameobject::Gameobject(){}

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